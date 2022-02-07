using UnityEngine;
using System.Collections;

public class skill : MonoBehaviour
{
	int cool_time;
	float last_skill_time;
	public bool skill_on;
	float fix_time;

	void Start()
	{
		cool_time = 4;
		last_skill_time = 0;
		skill_on = false;
		fix_time = 0;
	}

	void Update()
	{
		if(skill_on == false && Input.GetKeyDown(KeyCode.E))
			skill_on = true;
		else if(skill_on == true && Input.GetKeyDown(KeyCode.E))
			skill_on = false;

		if(skill_on == true)
		{
			if (Input.GetKeyDown(KeyCode.Alpha1) && cool_time + last_skill_time < Time.fixedTime) 
			{
				StartCoroutine("Skill_1");
			}
			else if (Input.GetKeyDown(KeyCode.Alpha2) && cool_time + last_skill_time < Time.fixedTime) 
			{
				StartCoroutine("Skill_2");
			}
			else if (Input.GetKeyDown(KeyCode.Alpha3) && cool_time + last_skill_time < Time.fixedTime) 
			{
				StartCoroutine("Skill_3");
			}
		}

	}

	IEnumerator Skill_1()//power overwhelming
	{
		last_skill_time = Time.fixedTime;
		GetComponent<unit>().morale_state = Morale_state.over_power;
		GetComponent<unit>().morale = GetComponent<unit>().max_morale;
		yield return new WaitForSeconds(3);
		GetComponent<unit>().morale_state = Morale_state.attention;
		skill_on = false;
	}
	IEnumerator Skill_2()//suppressing fire
	{
		last_skill_time = Time.fixedTime;
		this.GetComponent<shoot>().skill_1_call = true;
		for(int i = 0; i < GetComponent<squad>().open_member_count; i++)
			GetComponent<squad>().squad_member[i].GetComponent<npcfire>().skill_1_call = true;
		yield return new WaitForSeconds(3);
		for(int i = 0; i < GetComponent<squad>().open_member_count; i++)
			GetComponent<squad>().squad_member[i].GetComponent<npcfire>().skill_1_call = false;
		this.GetComponent<shoot>().skill_1_call = false;
		skill_on = false;
	}
	IEnumerator Skill_3()//precision fire
	{
		last_skill_time = Time.fixedTime;
		this.GetComponent<shoot>().skill_2_call = true;
		for(int i = 0; i < GetComponent<squad>().open_member_count; i++)
			GetComponent<squad>().squad_member[i].GetComponent<npcfire>().skill_2_call = true;
		yield return new WaitForSeconds(3);
		for(int i = 0; i < GetComponent<squad>().open_member_count; i++)
			GetComponent<squad>().squad_member[i].GetComponent<npcfire>().skill_2_call = false;
		this.GetComponent<shoot>().skill_2_call = false;
		skill_on = false;
	}
}