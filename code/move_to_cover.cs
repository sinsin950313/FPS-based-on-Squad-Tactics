using UnityEngine;
using System.Collections;

public class move_to_cover : MonoBehaviour
{
    public int cover_count;
    public int random_count;

    public Vector3 cover_vector;
    public float cover_vector_angle;
    public int find_cover_count = 0;

    public GameObject cover;

    void Update()
    {
        cover_count = this.gameObject.GetComponentInParent<unit>().squad.GetComponentInParent<unit>().GetComponentInChildren<morale_and_combat_area>().cover_list.Count;
    }

    public void Find_cover()
    {
        if(cover_count > 0)
        {
            for(find_cover_count = 0; find_cover_count < 5; find_cover_count++)
            {
                random_count = Random.Range(0,20);
                random_count = random_count % cover_count;
				cover = this.gameObject.GetComponentInParent<unit>().squad.GetComponentInParent<unit>().GetComponentInChildren<morale_and_combat_area>().cover_list[random_count];
                cover_vector = cover.transform.position - this.transform.position;
                cover_vector_angle = Vector3.Angle(this.transform.forward, cover_vector);
    
                if(cover_vector_angle < this.GetComponentInChildren<Camera>().fieldOfView)
                {
                    this.GetComponent<AIPath>().target.transform.position = cover.transform.position;
                    goto re_;
                }
            }
        }

    re_:;

    }
}

