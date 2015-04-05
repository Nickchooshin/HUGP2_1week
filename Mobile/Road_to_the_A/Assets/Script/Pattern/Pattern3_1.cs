﻿using UnityEngine;
using System.Collections;

public class Pattern3_1 : Pattern_State
{
	private GameObject obj_safe;
	private GameObject[] obj_warning = new GameObject[4];

	void Start ()
	{
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
				obj_warning[i].transform.localScale = new Vector3(12.0f, 245.0f, 0.0f);
				obj_warning[i].gameObject.SetActive(false);
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
			obj_warning [i].SetActive (true);

			if( 2 == i )
			{
				obj_warning[i].transform.localPosition = new Vector3(-5.0f, 73.0f, 0.0f);
				obj_warning[i].GetComponent<Enemy3_1> ()._finish = new Vector3(-613.0f, -286.0f, 0.0f);
				obj_warning[i].GetComponent<Enemy3_1> ().move_check = true;
			}
			else if( 3 == i )
			{
				Debug.Log("다록");
				obj_warning[i].transform.localPosition = new Vector3(86.0f, 68.0f, 0.0f);
				obj_warning[i].GetComponent<Enemy3_1> ()._finish = new Vector3(612.0f, -286.0f, 0.0f);
				obj_warning[i].GetComponent<Enemy3_1> ().move_check = true;
			}
		}
		yield return new WaitForSeconds(0.5f);
	}
}