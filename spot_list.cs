using UnityEngine;
using System.Collections;

public class spot_list : MonoBehaviour
{
    /*          head
     *          front
     *          back
     * left_arm     right_arm
     * left_foot    right_foot
     */

    public const int spot_point_count = 7;
    public int spot_point_count_ = spot_point_count;
    public GameObject[] spot_point = new GameObject[spot_point_count];

    void Awake()
    {
        //spot_point[1] = this.gameObject.transform.FindChild("gun").FindChild("F.spot_point").gameObject;
    }
}