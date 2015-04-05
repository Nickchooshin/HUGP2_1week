using UnityEngine;
using System.Collections;

public class Pattern1_1 : Pattern_State
{
	private GameObject obj_safe;
	private GameObject[] obj_warning = new GameObject[2];
	private GameObject[] obj_caution = new GameObject[2];

	void Start () 
	{
		// safe
		obj_safe = Instantiate (Resources.Load ("Boss1_1", typeof(GameObject))) as GameObject;
		obj_safe.transform.parent = GameObject.Find ("Boss").transform;
		obj_safe.transform.localScale = new Vector3(560.0f, 610.0f, 0.0f);
		obj_safe.transform.localPosition = new Vector3(0.0f, -20.0f, 0.0f);
		obj_safe.gameObject.SetActive(false);

		for( int i = 0; i < 2; ++i )
		{
			// Enemy
			obj_warning[i] = Instantiate (Resources.Load ("Boss1_2", typeof(GameObject))) as GameObject;
			obj_warning[i].transform.parent = GameObject.Find ("Boss").transform;
			obj_warning[i].transform.localScale = new Vector3(400.0f, 580.0f, 0.0f);
			obj_warning[i].gameObject.SetActive(false);

			if( 0 == i )
				obj_warning[i].transform.localPosition = new Vector3(-290.0f, 0.0f, 0.0f);
			else if( 1 == i )
				obj_warning[0].transform.localPosition = new Vector3(290.0f, 0.0f, 0.0f);
		}

		// caution
		obj_caution[0] = Instantiate (Resources.Load ("Warning_back", typeof(GameObject))) as GameObject;
		obj_caution[0].transform.parent = GameObject.Find ("Boss").transform;
		obj_caution[0].transform.localScale = new Vector3(400.0f, 720.0f, 0.0f);
		obj_caution[0].gameObject.SetActive(false);

		obj_caution[1] = Instantiate (Resources.Load ("Warning_guide", typeof(GameObject))) as GameObject;
		obj_caution[1].transform.parent = GameObject.Find ("Boss").transform;
		obj_caution[1].transform.localScale = new Vector3(250.0f, 250.0f, 0.0f);
		obj_caution[1].gameObject.SetActive(false);

		Move ();
	}

	void FixedUpdate ()
	{

	}

	public override void Move ()
	{
		StartCoroutine ("Change_Image");


	}

	void Sound_Play(  )
	{

	}

	IEnumerator Change_Image()
	{
		obj_safe.SetActive (true);
		yield return new WaitForSeconds(2.5f);

		DestroyObject (obj_safe);
		yield return new WaitForSeconds(0.5f);

		for( int i = 0; i < 2; ++i )
		{
			obj_caution[i].transform.localPosition = new Vector3(-290.0f, 0.0f, 0.0f);
			obj_caution[i].SetActive(true);
		}
		yield return new WaitForSeconds(1.0f);

		for( int i = 0; i < 2; ++i )
		{
			obj_caution[i].SetActive(false);
		}
		yield return new WaitForSeconds(0.2f);

		obj_warning[0].transform.localPosition = new Vector3(-290.0f, 0.0f, 0.0f);
		obj_warning[0].SetActive (true);
		yield return new WaitForSeconds(0.2f);

		for( int i = 0; i < 2; ++i )
		{
			obj_caution[i].transform.localPosition = new Vector3(290.0f, 0.0f, 0.0f);
			obj_caution[i].SetActive(true);
		}
		yield return new WaitForSeconds(0.3f);

		DestroyObject (obj_warning [0]);
		yield return new WaitForSeconds(0.7f);

		for( int i = 0; i < 2; ++i )
			DestroyObject (obj_caution[i]);
		yield return new WaitForSeconds(0.2f);

		obj_warning[1].transform.localPosition = new Vector3(290.0f, 0.0f, 0.0f);
		obj_warning[1].SetActive (true);
		yield return new WaitForSeconds(0.5f);

		DestroyObject (obj_warning [1]);
	}
}