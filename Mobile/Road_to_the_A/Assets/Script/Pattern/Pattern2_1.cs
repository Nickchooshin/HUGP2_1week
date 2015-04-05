using UnityEngine;
using System.Collections;

public class Pattern2_1 : Pattern_State
{
	private GameObject obj_safe;
	private GameObject[] obj_warning = new GameObject[3];
	private GameObject[] obj_caution = new GameObject[2];

	void Start ()
	{
		// safe
		obj_safe = Instantiate (Resources.Load ("Boss2_1", typeof(GameObject))) as GameObject;
		obj_safe.transform.parent = GameObject.Find ("Boss").transform;
		obj_safe.transform.localScale = new Vector3(460.0f, 580.0f, 0.0f);
		obj_safe.gameObject.SetActive(false);

		for( int i = 0; i < 3; ++i )
		{
			// Enemy
			obj_warning[i] = Instantiate (Resources.Load ("Boss2_2", typeof(GameObject))) as GameObject;
			obj_warning[i].transform.parent = GameObject.Find ("Boss").transform;
			obj_warning[i].transform.localScale = new Vector3(300.0f, 300.0f, 0.0f);
			obj_warning[i].gameObject.SetActive(false);
		}

		// caution
		obj_caution[0] = Instantiate (Resources.Load ("Warning_back", typeof(GameObject))) as GameObject;
		obj_caution[0].transform.parent = GameObject.Find ("Boss").transform;
		obj_caution[0].transform.localScale = new Vector3(300.0f, 720.0f, 0.0f);
		obj_caution[0].GetComponent<Warning> ().chase_check = true;
		obj_caution[0].gameObject.SetActive(false);
		
		obj_caution[1] = Instantiate (Resources.Load ("Warning_guide", typeof(GameObject))) as GameObject;
		obj_caution[1].transform.parent = GameObject.Find ("Boss").transform;
		obj_caution[1].transform.localScale = new Vector3(200.0f, 200.0f, 0.0f);
		obj_caution[1].GetComponent<Warning> ().chase_check = true;
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

	public IEnumerator Change_Image()
	{
		obj_safe.transform.localPosition = new Vector3(0.0f, -10.0f, 0.0f);
		obj_safe.gameObject.SetActive(true);
		yield return new WaitForSeconds(3.0f);

		DestroyObject (obj_safe);
		yield return new WaitForSeconds(0.3f);
		
		for( int i = 0; i < 2; ++i )
			obj_caution[i].gameObject.SetActive(false);
		yield return new WaitForSeconds(1.5f);

		for( int i = 0; i < 2; ++i )
			obj_caution[i].GetComponent<Warning> ().chase_check = true;

		for( int i = 0; i < 3; ++i )
		{
			for( int j = 0; j < 2; ++j )
				obj_caution[j].gameObject.SetActive(true);
			yield return new WaitForSeconds(1.5f);

			for( int j = 0; j < 2; ++j )
				obj_caution[j].gameObject.SetActive(false);
				
			yield return new WaitForSeconds(0.5f);
			
			obj_warning[i].SetActive(true);
			obj_warning[i].transform.localPosition =
				new Vector3(obj_caution[0].transform.localPosition.x, 500.0f, 0.0f);
			yield return new WaitForSeconds(0.2f);
		}
		for (int i = 0; i < 2; ++i)
			DestroyObject (obj_caution [i]);
		yield return new WaitForSeconds(2.1f);

		for (int i = 0; i < 3; ++i)
			DestroyObject (obj_warning [i]);
	}
}