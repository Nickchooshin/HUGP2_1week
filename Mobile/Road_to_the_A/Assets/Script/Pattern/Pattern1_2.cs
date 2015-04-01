using UnityEngine;
using System.Collections;

public class Pattern1_2 : Pattern_State
{
	private GameObject[] obj_warning = new GameObject[9];
	
	private float m_time;
	
	void Start () 
	{
		// Warning Setting
		for( int i = 0; i < 9; ++i )
		{
			obj_warning[i] = Instantiate (Resources.Load ("Boss1_3", typeof(GameObject))) as GameObject;
			obj_warning[i].transform.parent = GameObject.Find ("Boss").transform;
			obj_warning[i].transform.localScale = new Vector3(200.0f, 300.0f, 0.0f);
			obj_warning[i].gameObject.SetActive(false);
		}
		
		m_time = Time.time;

		Move ();
	}
	
	void FixedUpdate ()
	{
		
	}
	
	public override void Move ()
	{
		for (int i = 0; i < 7; ++i)
			StartCoroutine ("Change_Image");
	}
	
	IEnumerator Change_Image()
	{
		yield return new WaitForSeconds(5.0f);

		for( int i = 0; i < 3; ++i )
		{
			obj_warning[i].transform.localPosition = new Vector3(350.0f + (i * 400.0f), -425.0f, 0.0f);
			obj_warning[i].gameObject.SetActive(true);
		}
		yield return new WaitForSeconds(0.3f);

		for( int i = 3; i < 6; ++i )
		{
			obj_warning[i].transform.localPosition = new Vector3(350.0f + (i * 400.0f), -425.0f, 0.0f);
			obj_warning[i].gameObject.SetActive(true);
		}
		yield return new WaitForSeconds(0.2f);
		
		for( int i = 0; i < 3; ++i )
		{
			DestroyObject(obj_warning[i]);
		}
		yield return new WaitForSeconds(0.1f);

		for( int i = 6; i < 9; ++i )
		{
			obj_warning[i].transform.localPosition = new Vector3(350.0f + (i * 400.0f), -425.0f, 0.0f);
			obj_warning[i].gameObject.SetActive(true);
		}
		yield return new WaitForSeconds(0.2f);

		for( int i = 3; i < 6; ++i )
		{
			DestroyObject(obj_warning[i]);
		}
		yield return new WaitForSeconds(0.3f);
		
		for( int i = 6; i < 9; ++i )
		{
			DestroyObject(obj_warning[i]);
		}
	}
}