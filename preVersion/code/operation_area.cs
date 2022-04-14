using UnityEngine;
using System.Collections;

public class operation_area : MonoBehaviour
{
	public GameObject enemy;
	public GameObject team_member;

	void OnTriggerStay(Collider collider)
	{
		int i;
		int member_count = this.GetComponent<squad>().open_member_count;
		if((collider.gameObject.tag == "Player" || collider.gameObject.tag == "NPC") && 
		   collider.gameObject.GetComponentInParent<unit>().attached != this.gameObject.GetComponent<squad>().attached && 
		   collider.GetComponent<unit>().live_or_dead == true)
		{
			enemy = collider.gameObject;
			for(i = 0; i < member_count; i++)
			{
				this.gameObject.GetComponent<squad>().squad_member[i].gameObject.GetComponentInChildren<camera_spot_check>().visible_check(ref enemy);
				//enemy.GetComponentInChildren<camera_spot_check> ().visible_check(ref team_member);
			}
			enemy = null;
		}
	}

	public void OnTriggerExit(Collider collider)
	{
		if((collider.gameObject.tag == "Player" || collider.gameObject.tag == "NPC") && collider.gameObject.GetComponentInParent<unit>().attached != this.gameObject.GetComponentInChildren<unit>().attached)
		{
			enemy = collider.gameObject;
			enemy.GetComponent<unit>().visible = false;
			this.gameObject.GetComponent<unit>().visible = false;
            if(this.gameObject.GetComponentInParent<unit>().GetComponentInChildren<squad>().enemy_spot_list.IndexOf(enemy) == -1)
			    this.gameObject.GetComponentInParent<squad>().enemy_spot_list.Remove(enemy);
			enemy = null;
		}
	}
}
