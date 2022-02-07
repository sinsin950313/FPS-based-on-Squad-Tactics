using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public enum Formation {Diamond};
public enum Squad_Combat_State {attention, combat};

public class squad : MonoBehaviour
{
    public const int member_count = 3;

	public int open_member_count = member_count;

	private int i,j;

    public GameObject member_model;

    public GameObject member_position_model;

	public GameObject[] squad_member = new GameObject[member_count];

    public GameObject[] position = new GameObject[member_count];

	public Attached attached;//소속

    public Formation formation;//진형

	public Squad_Combat_State squad_combat_state;

	//public string squad_state;//hold_fire first_strike

	//public string squad_skill;//분대 기술

	public List<GameObject> enemy_spot_list = new List<GameObject>();//스팟 된 적군

	void Start ()
	{
        attached = this.gameObject.GetComponentInParent<unit> ().attached;
		formation = Formation.Diamond;
		squad_combat_state = Squad_Combat_State.attention;

        ////instatiate squad member and set their options
        for (i=0; i<member_count; i++)
        {
            position[i] = Instantiate(member_position_model, this.transform.position, this.transform.rotation)as GameObject;
			position[i].transform.parent = this.gameObject.GetComponentInParent<unit>().transform;//this.gameObject.transform;
            position[i].transform.localPosition = new Vector3(5 * (-i + 1), 3, (Mathf.Abs(-i + 1) - 1) * 5);
            squad_member[i] = Instantiate(member_model, position[i].transform.position ,this.transform.rotation)as GameObject;
            squad_member[i].tag = "NPC";
			string unit_tag = squad_member[i].tag;
			GameObject squadmember = squad_member[i].gameObject;
			GetComponentInParent<NetworkManager>().Start_script(ref unit_tag, ref squadmember);
			squad_member[i].GetComponent<unit>().squad = this.GetComponent<squad>();
            squad_member[i].GetComponent<AIPath>().target = this.position[i].transform;
            squad_member[i].GetComponent<unit>().attached = this.attached;
			//squad_member[i].name = this.gameObject.GetComponentInChildren<unit>().name + i;
        }
	}

	void Update ()
	{
		if(enemy_spot_list.Count > 0)
		{
			for(i = 0 ; i < member_count; i++)
			{
				for(j = 0 ; j < enemy_spot_list.Count ; j++)
				{
					squad_member[i].GetComponentInChildren<camera_spot_check>().combat_able(enemy_spot_list[j]);

					if(enemy_spot_list[j].GetComponent<unit>().live_or_dead == false)
					{
						enemy_spot_list.RemoveAt(j);
						squad_member[i].GetComponentInChildren<camera_spot_check>().target = null;
						squad_member[i].GetComponentInChildren<camera_spot_check>().target_vector.x = 0;
						squad_member[i].GetComponentInChildren<camera_spot_check>().target_vector.y = 0;
						squad_member[i].GetComponentInChildren<camera_spot_check>().target_vector.z = 0;
					}
				}
			}
     	}
        
        if(this.gameObject.GetComponentInParent<unit>().GetComponentInChildren<morale_and_combat_area>().cover_list.Count == 0 || 
		   squad_combat_state != Squad_Combat_State.combat)
        {
            Re_Positioning();
        }
	}

    void Re_Positioning()
	{
		for (i=0; i<member_count; i++)
		{
			if(this.GetComponentInParent<FPSInputController>().directionVector.magnitude == 0
			   /* && squad_member[i].transform.position - position[i].transform.position*/)
			{
				squad_member[i].GetComponent<AIPath>().enabled = false;
				squad_member[i].transform.forward = this.GetComponentInParent<unit>().transform.forward;
			}
			
			else
			{
				squad_member[i].GetComponent<AIPath>().enabled = true;
			}
		}

		if(this.formation == Formation.Diamond)
		{
			for (i=0; i < member_count; i++)
			{
				position[i].transform.localPosition = new Vector3(5 * (-i + 1), 3, (Mathf.Abs(-i + 1) - 1) * 5);
			}
		}
    }
}
