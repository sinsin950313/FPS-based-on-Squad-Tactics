using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class morale_and_combat_area : MonoBehaviour
{
    public List<GameObject> cover_list = new List<GameObject>();
	public int random_value;

	void OnTriggerStay(Collider collider)
    {
		if(collider.gameObject.tag == "cover" && cover_list.IndexOf(collider.gameObject) == -1)
		{
			cover_list.Add(collider.gameObject);
			//Add_cover_list(ref collider);
		}
    }
    
    void OnTriggerExit(Collider collider)
    {
		if(collider.gameObject.tag == "cover" && cover_list.IndexOf(collider.gameObject) != -1)
		{
			cover_list.Remove(collider.gameObject);
			//Remove_cover_list(ref collider);
		}
    }
	/*
	void Add_cover_list(ref Collider collider)
	{
		int i;
		int member_count = this.GetComponentInParent<unit>().GetComponentInChildren<squad>().open_member_count;

		for(i = 0; i < member_count; i++)
		{
			cover_list.Add(collider.gameObject);
		}
	}

	void Remove_cover_list(ref Collider collider)
	{
		int i;
		int member_count = this.GetComponentInParent<unit>().GetComponentInChildren<squad>().open_member_count;
		for(i = 0; i < member_count; i++)
		{
			cover_list.Remove(collider.gameObject);
		}
	}
	*/
}

