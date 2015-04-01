using UnityEngine;
using System.Collections;

public class Pattern1_1 : Pattern_State
{
	private GameObject obj_safe;
	private GameObject[] obj_warning = new GameObject[2];

	private float m_time;

	void Start () 
	{
		// Safe Object Setting
		obj_safe = Instantiate (Resources.Load ("Boss1_1", typeof(GameObject))) as GameObject;
		obj_safe.transform.parent = GameObject.Find ("Boss").transform;
		obj_safe.transform.localScale = new Vector3(560.0f, 610.0f, 0.0f);
		obj_safe.gameObject.SetActive(false);

		for( int i = 0; i < 2; ++i )
		{
			obj_warning[i] = Instantiate (Resources.Load ("Boss1_2", typeof(GameObject))) as GameObject;
			obj_warning[i].transform.parent = GameObject.Find ("Boss").transform;
			obj_warning[i].transform.localScale = new Vector3(400.0f, 580.0f, 0.0f);
			obj_warning[i].gameObject.SetActive(false);
		}

		m_time = Time.time;
	}

	void FixedUpdate ()
	{
	
	}

	public override void Move ()
	{
		for (int i = 0; i < 6; ++i)
			StartCoroutine ("Change_Image");
	}

	IEnumerator Change_Image()
	{
		obj_safe.transform.localPosition = new Vector3(0.0f, 412.0f, 0.0f);
		obj_safe.gameObject.SetActive(true);
		yield return new WaitForSeconds(3.0f);

		DestroyObject (obj_safe);
		yield return new WaitForSeconds(1.7f);
		
		obj_warning[0].transform.localPosition = new Vector3(350.0f, -425.0f, 0.0f);
		obj_warning[0].gameObject.SetActive(true);
		yield return new WaitForSeconds(0.5f);
		
		DestroyObject (obj_warning[0]);
		yield return new WaitForSeconds(0.9f);
		
		obj_warning[1].transform.localPosition = new Vector3(350.0f, -425.0f, 0.0f);
		obj_warning[1].gameObject.SetActive(true);
		yield return new WaitForSeconds(0.5f);

		DestroyObject (obj_warning[1]);
	}
}