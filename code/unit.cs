using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public enum Morale_state {over_power, attention, suppress, pinned};
public enum Attached {Red_Team, Blue_Team, None};//소속

public struct hit_log
{
	public GameObject Shooter;
    //Attached Attached;
    public int Demage;

    public hit_log(ref GameObject shooter/*, ref Attached attached*/, ref int demage)
    {
        Shooter = shooter;
        //Attached = attached;
        Demage = demage;
    }
};

public class unit : MonoBehaviour
{
    public string name;

	public string unit_tag;

	public GameObject Unit;

	public int score = 0;

	public int value = 100;//function(ref training etc)

	public squad squad;

	public string gun_name;

	public Attached attached;

	//public string position;

    public bool live_or_dead;

	public int health;

	private int max_health = 9000;

	public float hit_time;

	private float recovery_time = 7f;

	public int training = 100;//훈련도

	public int max_morale;//최대 사기

	public int morale;//사기

	public float morale_hit_time;//제압시간

	public float morale_recovery_time = 10;//회복시간

	public List<hit_log> hit_by_who = new List<hit_log>();

    public Morale_state morale_state;

    /// <summary>
    /// unit camo data -> unit
    /// </summary>
    public int sight_range = 100;//function(ref gun_weight, ref bullet_weight, ref bullet_count, ref armor_weight, ref head_set_data, etc)//무거울수록 반비례.
    public int max_camopoint = 100;//function(ref armor_camo, ref training, etc)
    public int real_camopoint;//function
    
    public bool visible = false;//볼수있음.//result
    public bool spot = false;//미니맵에 나옴.//result

	/// <summary>
	/// respawn_time
	/// </summary>
	
	float respawn_call_time = Time.fixedTime;
	float respawn_need_time = 1f;

	void Start()
	{
		unit_tag = this.gameObject.tag;
		Unit = this.gameObject;

		morale = max_morale = training * 3;
		morale_state = Morale_state.attention;
		health = max_health;
		live_or_dead = true;
		gun_name = this.gameObject.GetComponentInChildren<gun>().name;
	}

	void Update()
    {
		if(live_or_dead == false && respawn_call_time + respawn_need_time < Time.fixedTime)
		{
			if(unit_tag == "Player")
				GetComponentInParent<NetworkManager>().Respawn_script(ref unit_tag, ref Unit);
		}

        if(health <= 0)
        {
            live_or_dead = false;
			Calculate_score();
			if(unit_tag == "Player")
				GetComponentInParent<NetworkManager>().Dead_script(ref unit_tag, ref Unit);
        }

		if(hit_time + recovery_time < Time.fixedTime)
		{
			health = max_health;
			hit_by_who.Clear();
		}

		if(morale < max_morale && morale_hit_time + 1f < Time.fixedTime && morale_state != Morale_state.over_power)
		{
			morale += 7;
			morale = Mathf.Min(max_morale,morale);
			morale_hit_time = Time.fixedTime;
		}

		if(morale <= max_morale * 0.3)
        {
            morale_state = Morale_state.pinned;;
			morale = Mathf.Max(morale,0);
		}

		else if(morale < max_morale * 0.5)
		{
            morale_state = Morale_state.suppress;
		}
		else
        {
            morale_state = Morale_state.attention;
		}
	}

	void Calculate_score()
	{
		foreach(hit_log hit_data in hit_by_who)
		{
			hit_data.Shooter.GetComponent<unit>().score += (int)(hit_data.Demage / 10 * value / 10);
		}
	}

	/*
    void Start_script(ref string tag)
	{
		this.gameObject.AddComponent<CharacterMotor>();
		controller = GetComponent<CharacterController>();
		controller.height = 1.2f;
		controller.radius = 0.2f;
		controller.center = new Vector3(0, 0.6f, 0);

        if(this.gameObject.tag == "Player")
        {
            this.gameObject.AddComponent<FPSInputController>();
            this.gameObject.AddComponent<keyboardcontrol>();
            this.gameObject.GetComponentInChildren<Camera>().gameObject.AddComponent<mousecontrol>();

            ///operation area

            operation_area = Resources.LoadAssetAtPath("Assets/prefab/operation_area.prefab",typeof(GameObject)) as GameObject;
            operation_area = Instantiate(operation_area,this.transform.position, this.transform.rotation) as GameObject;
            operation_area.transform.parent = this.gameObject.transform;
			//operation_area.tag = "operation_area";
			squad = this.gameObject.GetComponentInChildren<operation_area>().GetComponent<squad>();

            ///mouselook

            this.gameObject.transform.FindChild("body_up").gameObject.AddComponent<MouseLook>().axes = MouseLook.RotationAxes.MouseY;
            this.gameObject.AddComponent<MouseLook>().axes = MouseLook.RotationAxes.MouseX;
            this.gameObject.GetComponentInChildren<Camera>().gameObject.AddComponent<MouseLook>().axes = MouseLook.RotationAxes.MouseY;

			///morale_and_combat_area

			morale_and_combat_area = Resources.LoadAssetAtPath("Assets/prefab/morale_and_combat_area.prefab",typeof(GameObject)) as GameObject;
			morale_and_combat_area = Instantiate(morale_and_combat_area, this.transform.position, this.transform.rotation) as GameObject;
			morale_and_combat_area.transform.parent = this.gameObject.transform;

        }

        else
        {
            this.gameObject.AddComponent<AIPath>();
            this.gameObject.AddComponent<move_to_cover>();
        }
    }

    void Dead_script(ref string tag)
    {
        //this.GetComponent<unit>().enabled = false;
        this.GetComponentInChildren<camera_spot_check>().enabled = false;
        this.GetComponentInChildren<Invese_Kinematics>().enabled = false;
        //this.GetComponentInChildren<morale_and_combat_area>().enabled = false;
        this.GetComponent<spot_list>().enabled = false;

        if(this.gameObject.tag == "Player")
        {
            this.GetComponentInChildren<shoot>().enabled = false;
            this.GetComponent<CharacterMotor>().enabled = false;
            this.GetComponent<CharacterController>().enabled = false;
            this.GetComponent<FPSInputController>().enabled = false;
            //this.GetComponent<keyboardcontrol>().enabled = false;
            this.gameObject.GetComponentInChildren<MouseLook>().enabled = false;
			this.gameObject.transform.FindChild("body_up").GetComponentInChildren<MouseLook>().enabled = false;
            this.gameObject.transform.FindChild("Camera").GetComponentInChildren<MouseLook>().enabled = false;
            this.GetComponentInChildren<mousecontrol>().enabled = false;
            this.GetComponentInChildren<operation_area>().enabled = false;
            //this.GetComponentInChildren<squad>().enabled = false;
        }

        else
        {
            this.GetComponentInChildren<npcfire>().enabled = false;
            this.GetComponent<move_to_cover>().enabled = false;
            this.GetComponent<AIPath>().enabled = false;
            //this.GetComponent<Seeker>().enabled = false;
        }
    }

	void Respown_script(ref string tag)
	{
		this.GetComponentInChildren<camera_spot_check>().enabled = true;
		this.GetComponentInChildren<Invese_Kinematics>().enabled = true;
		//this.GetComponentInChildren<morale_and_combat_area>().enabled = false;
		this.GetComponent<spot_list>().enabled = true;
		
		if(this.gameObject.tag == "Player")
		{
			this.GetComponentInChildren<shoot>().enabled = true;
			this.GetComponent<CharacterMotor>().enabled = true;
			this.GetComponent<CharacterController>().enabled = true;
			this.GetComponent<FPSInputController>().enabled = true;
			//this.GetComponent<keyboardcontrol>().enabled = false;
			this.gameObject.GetComponentInChildren<MouseLook>().enabled = true;
			this.gameObject.transform.FindChild("body_up").GetComponentInChildren<MouseLook>().enabled = true;
			this.gameObject.transform.FindChild("Camera").GetComponentInChildren<MouseLook>().enabled = true;
			this.GetComponentInChildren<mousecontrol>().enabled = true;
			this.GetComponentInChildren<operation_area>().enabled = true;
			//this.GetComponentInChildren<squad>().enabled = false;
		}
		
		else
		{
			this.GetComponentInChildren<npcfire>().enabled = true;
			this.GetComponent<move_to_cover>().enabled = true;
			this.GetComponent<AIPath>().enabled = true;
			//this.GetComponent<Seeker>().enabled = false;
		}
	}
	*/
}
