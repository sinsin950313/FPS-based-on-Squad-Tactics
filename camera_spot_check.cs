using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public struct Camo_data
{
    /// <summary>
    /// unit camo data -> unit
    /// </summary>
    public int sight_range;
    public int max_camopoint;
    public int real_camopoint;
    /// <summary>
    /// movement camo data -> FPSinputcontroller + suit
    /// </summary>
    //public int walk_camo_down;
    //public int real_walk;
    //public int run_camo_down;
    //public int real_run;
    /// <summary>
    /// shooting camo data -> movebullet + shoot
    /// </summary>
    //public int shoot_count;
    //public int if_do_shoot;
    //public int camo_bullet_size;
    
    public Camo_data(ref int Sight_range, ref int Max_camopoint,
                     ref int Real_camopoint//, ref int Walk_camo_down,
                     //ref int Real_walk, ref int Run_camo_down,
                     //ref int Real_run, ref int Shoot_count,
                     //ref int If_do_shoot, ref int Camo_bullet_size
	                 )
    {
        sight_range = Sight_range;
        max_camopoint = Max_camopoint;
        real_camopoint = Real_camopoint;
        //walk_camo_down = Walk_camo_down;
        //real_walk = Real_walk;
        //run_camo_down = Run_camo_down;
        //real_run = Real_run;
        //shoot_count = Shoot_count;
        //if_do_shoot = If_do_shoot;
        //camo_bullet_size = Camo_bullet_size;
    }
};

public class camera_spot_check : MonoBehaviour 
{
    /// <summary>
    /// enemy & vector
    /// </summary>
    public Ray ray;

    public GameObject enemy_spot_point;

	public Vector3 enemy_vector;
	
	public Vector3 enemy_spot_point_vector;
	
	public RaycastHit hit;
	
	public int spot_count;

    /// <summary>
    /// NPC & enemy
    /// </summary>
    
    public Transform target;

    public float dist_to_target;

    public Vector3 target_vector;
    
    public float sight_angle;

    /// <summary>
    /// grass camo data -> camera_spot_check
    /// </summary>
    private int grasscamo = 10;

    private int real_grass;

    public Camo_data camo_data;

    public int spot_able;

    public Transform aim;

    void Start()
    {
        if(this.GetComponentInParent<unit>().tag == "Player")
        {
            camera.camera.enabled = true;
            camera.GetComponent<AudioListener>().enabled = true;
            
            aim = Resources.LoadAssetAtPath("Assets/prefab/position.prefab", typeof(Transform)) as Transform;
            aim = Instantiate(aim, this.transform.position, this.transform.rotation) as Transform;
            aim.parent = this.transform;
            aim.transform.localPosition = new Vector3(0, 0, 100);
        }
    }

	public void visible_check(ref GameObject enemy)
    {
        spot_count = enemy.GetComponentInChildren<spot_list>().spot_point_count_;
        ////search object pool
        camo_data = new Camo_data(ref enemy.GetComponent<unit>().sight_range, ref enemy.GetComponent<unit>().max_camopoint, ref enemy.GetComponent<unit>().real_camopoint
                                  //ref enemy.GetComponentInChildren<FPSInputController>().walk_camo_down, ref enemy.GetComponent<FPSInputController>().real_walk ,
                                  //ref enemy.GetComponent<FPSInputController>().run_camo_down, ref enemy.GetComponent<FPSInputController>().real_run,
                                  //ref enemy.GetComponentInChildren<shoot>().shoot_count, ref enemy.GetComponent<shoot>().if_do_shoot,
                                  //ref enemy.GetComponentInChildren<gun>().camo_bullet_size
		                          );
        enemy_vector = enemy.transform.position - this.transform.position;
		//enemy_spot_point = enemy.GetComponentsInChildren<spot_point> ();_count = 0;
		spot_count = 0;

    re:;

        for(; spot_count < 7; spot_count++)
		{
			enemy_spot_point = enemy.gameObject.GetComponentInChildren<spot_list>().spot_point[spot_count];
            enemy_spot_point_vector = enemy_spot_point.transform.position - this.transform.position;
			//enemy_spot_point_vector = enemy_spot_point[spot_count].transform.position - this.transform.position;
			ray = new Ray(this.transform.position, enemy_spot_point_vector);
			Debug.DrawRay(ray.origin, ray.direction, Color.red);

			if (Physics.Raycast(ray, out hit))
			{
                if(hit.collider.name == "wall")
                {
                    //Debug.Log("wall");
                    enemy.GetComponent<unit>().visible = false;
                    spot_count++;
                    goto re;
                }

				if (hit.collider.name == "grass")
				{
					//Debug.Log("grass");
                    real_grass = 1;
				}
        	}
            ////balance
            spot_able = Mathf.Max (this.gameObject.GetComponentInParent<unit> ().sight_range - (int)enemy_spot_point_vector.magnitude, 0);
            spot_able = Mathf.Min (spot_able, this.gameObject.GetComponentInParent<unit> ().sight_range);
			camo_data.real_camopoint = camo_data.max_camopoint ;//* (100 - ((walk_camo_down * real_walk) + (run_camo_down * real_run))) / 100 * (100 - shoot_count * if_do_shoot) / 100 + how_many_grass * grasscamo;
			camo_data.real_camopoint = Mathf.Min (camo_data.real_camopoint, camo_data.max_camopoint);

            ////compare camo_point & spot_able
			if(camo_data.real_camopoint >= spot_able)
			{
				enemy.GetComponent<unit>().visible = false;
			}

			else
			{
				enemy.GetComponent<unit>().visible = true;
				if(this.GetComponentInParent<unit>().squad.enemy_spot_list.IndexOf(enemy) == -1)
					this.gameObject.GetComponentInParent<unit>().squad.enemy_spot_list.Add(enemy);
			}

            ////if spot_count is end & enemy.visible is false then remove at lsit
            if(spot_count == 6 && enemy.GetComponent<unit>().visible == false)
            {
                this.gameObject.GetComponentInParent<unit>().GetComponentInChildren<squad>().enemy_spot_list.Remove(enemy);
            }

            ////clear grass data
            real_grass = 0;

            ////clear the enemy data
            spot_able = 0;
            enemy_vector.x = 0;
            enemy_vector.y = 0;
            enemy_vector.z = 0;
            enemy_spot_point = null;
            enemy_spot_point_vector.x = 0;
            enemy_spot_point_vector.y = 0;
            enemy_spot_point_vector.z = 0;
            ray.origin = this.transform.position;
            ray.direction = enemy_spot_point_vector;

            ////clear the structure
            camo_data = default(Camo_data);
		}
	}

	public void combat_able(GameObject enemy)
	{
		if(this.gameObject.GetComponentInParent<unit>().tag == "NPC")
		{
			if(this.GetComponentInParent<unit>().squad.enemy_spot_list.Count == 1)
			{
				target = enemy.transform;
			}

			////compare the distance to each targets
            target_vector = enemy.transform.position - this.transform.position;
            sight_angle = Vector3.Angle (target_vector, this.transform.forward);

            ////거리제한 & 시야각제한.
            if(enemy_vector.magnitude < this.GetComponentInParent<unit>().GetComponentInChildren<gun>().limit_distance 
               && sight_angle < this.camera.fieldOfView && enemy.GetComponent<unit>().visible ==true )
			{
				enemy.GetComponent<unit>().spot = true;
				this.gameObject.GetComponentInParent<unit>().squad.squad_combat_state = Squad_Combat_State.combat;

                if(target_vector.magnitude < dist_to_target)
				{
                    dist_to_target = target_vector.magnitude;
                    target = enemy.transform;
                }

                this.GetComponentInParent<unit>().gameObject.transform.LookAt(target);
				this.GetComponentInParent<move_to_cover>().Find_cover();
                this.gameObject.GetComponentInParent<unit>().GetComponentInChildren<npcfire>().fire(ref target);
            }

			else
			{
				enemy.GetComponent<unit>().spot = false;
				this.gameObject.GetComponentInParent<unit>().squad.squad_combat_state = Squad_Combat_State.attention;
			}
		}

		else if(this.gameObject.tag == "Player")
		{
			if(enemy_vector.magnitude < this.GetComponentInParent<unit>().GetComponentInChildren<gun>().limit_distance 
			   && sight_angle < this.camera.fieldOfView)
			{
                enemy.GetComponent<unit>().spot = true;
			}
		}
  	}
}