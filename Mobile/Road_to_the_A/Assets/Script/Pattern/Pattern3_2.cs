using UnityEngine;
using System.Collections;

public class Pattern3_2 : Pattern_State
{
	private GameObject obj_safe;
	private GameObject[] obj_warning = new GameObject[42];
	
	public bool end_check;
	
	void Start ()
	{
		end_check = false;

		// safe
		obj_safe = Instantiate (Resources.Load ("Boss3_4", typeof(GameObject))) as GameObject;
		obj_safe.transform.parent = GameObject.Find ("Boss").transform;
		obj_safe.transform.localScale = new Vector3(880.0f, 620.0f, 0.0f);
		obj_safe.gameObject.SetActive(false);
		
		for( int i = 0; i < 42; ++i )
		{
			obj_warning[i] = Instantiate (Resources.Load ("Boss3_5", typeof(GameObject))) as GameObject;
			obj_warning[i].transform.parent = GameObject.Find ("Boss").transform;
			obj_warning[i].transform.localScale = new Vector3(64.0f, 102.0f, 0.0f);
			obj_warning[i].gameObject.SetActive(false);
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
		obj_safe.transform.localPosition = new Vector3(-6.0f, 36.0f, 0.0f);
		obj_safe.gameObject.SetActive(true);
		yield return new WaitForSeconds(2.0f);

		obj_safe.GetComponent<Safe3_2>().move_check = true;
		yield return new WaitForSeconds(2.5f);

		for (int i = 0; i < 14; ++i)
		{
			obj_warning [i].transform.localPosition =
				new Vector3(Random.Range(-640.0f, 640.0f), 410.0f , 0.0f);
			obj_warning [i].SetActive (true);
		}
		yield return new WaitForSeconds(1.2f);

		for (int i = 14; i < 28; ++i)
		{
			obj_warning [i].transform.localPosition =
				new Vector3(Random.Range(-640.0f, 640.0f), 410.0f , 0.0f);
			obj_warning [i].SetActive (true);
		}
		yield return new WaitForSeconds(1.2f);
		
		for (int i = 28; i < 42; ++i)
		{
			obj_warning [i].transform.localPosition =
				new Vector3(Random.Range(-640.0f, 640.0f), 410.0f , 0.0f);
			obj_warning [i].SetActive (true);
		}
		yield return new WaitForSeconds(2.0f);

		DestroyObject (obj_safe);
		for( int i = 0; i < 42; ++i )
			DestroyObject (obj_warning[i]);
		end_check = true;
	}
}