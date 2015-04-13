using UnityEngine;
using System.Collections;

public class Pattern3_1 : Pattern_State
{
	private GameObject obj_safe;
	private GameObject[] obj_warning = new GameObject[4];

	public bool end_check;

	void Start ()
	{
		end_check = false;

		// safe
		obj_safe = Instantiate (Resources.Load ("Boss3_1", typeof(GameObject))) as GameObject;
		obj_safe.transform.parent = GameObject.Find ("Boss").transform;
		obj_safe.transform.localScale = new Vector3(580.0f, 620.0f, 0.0f);
		obj_safe.gameObject.SetActive(false);

		for( int i = 0; i < 4; ++i )
		{
			// Enemy
			if( 0 == i )
			{
				obj_warning[i] = Instantiate (Resources.Load ("Boss3_2", typeof(GameObject))) as GameObject;
				obj_warning[i].transform.parent = GameObject.Find ("Boss").transform;
				obj_warning[i].transform.localPosition = new Vector3(-5.0f, 73.0f, 0.0f);
				obj_warning[i].transform.localScale = new Vector3(30.0f, 30.0f, 0.0f);
				obj_warning[i].gameObject.SetActive(false);
			}
			else if( 1 == i )
			{
				obj_warning[i] = Instantiate (Resources.Load ("Boss3_2", typeof(GameObject))) as GameObject;
				obj_warning[i].transform.parent = GameObject.Find ("Boss").transform;
				obj_warning[i].transform.localPosition = new Vector3(86.0f, 68.0f, 0.0f);
				obj_warning[i].transform.localScale = new Vector3(30.0f, 30.0f, 0.0f);
				obj_warning[i].gameObject.SetActive(false);
			}
			else
			{
				obj_warning[i] = Instantiate (Resources.Load ("Boss3_3", typeof(GameObject))) as GameObject;
				obj_warning[i].transform.parent = GameObject.Find ("Boss").transform;
				obj_warning[i].transform.localScale = new Vector3(12.0f, 10.0f, 0.0f);
				obj_warning[i].gameObject.SetActive(false);
				if( 2 == i )
				{
					obj_warning[i].transform.localPosition = new Vector3(-5.0f, 73.0f, 0.0f);
					obj_warning[i].GetComponent<Enemy3_1> ()._to = new Vector3(-613.0f, -380.0f, 0.0f);
					obj_warning[i].GetComponent<Enemy3_1> ()._to2 = new Vector3(-10.0f, -380.0f, 0.0f);
				}
				else if( 3 == i )
				{
					obj_warning[i].transform.localPosition = new Vector3(86.0f, 68.0f, 0.0f);
					obj_warning[i].GetComponent<Enemy3_1> ()._to = new Vector3(613.0f, -430.0f, 0.0f);
					obj_warning[i].GetComponent<Enemy3_1> ()._to2 = new Vector3(10.0f, -430.0f, 0.0f);
				}
			}
		}

		Move ();
	}
	
	void Update ()
	{
		
	}

	public override void Move ()
	{
		StartCoroutine ("Change_Image");
	}

	IEnumerator Change_Image()
	{
		obj_safe.transform.localPosition = new Vector3(6.0f, -42.0f, 0.0f);
		obj_safe.gameObject.SetActive(true);
		yield return new WaitForSeconds(2.0f);

		for (int i = 0; i < 4; ++i)
		{
			if( 2 == i )
			{
				obj_warning[i].GetComponent<Enemy3_1> ().move_check = true;
				obj_warning[i].GetComponent<Enemy3_1> ().dir_check = false;
			}
			else if( 3 == i )
			{
				obj_warning[i].GetComponent<Enemy3_1> ().move_check = true;
				obj_warning[i].GetComponent<Enemy3_1> ().dir_check = true;
			}
			obj_warning [i].SetActive (true);
		}
		yield return new WaitForSeconds(2.5f);

		DestroyObject (obj_safe);
		for (int i = 0; i < 4; ++i)
			DestroyObject (obj_warning [i]);
		
		end_check = true;
	}
}