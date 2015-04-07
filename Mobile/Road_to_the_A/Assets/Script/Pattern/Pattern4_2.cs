using UnityEngine;
using System.Collections;

public class Pattern4_2 : Pattern_State
{
	private GameObject obj_boss;
	public Transform[] prefab = new Transform[2];
	
	public bool end_check;
	
	void Start ()
	{
		end_check = false;

		obj_boss = Instantiate (Resources.Load ("Boss4_4", typeof(GameObject))) as GameObject;
		obj_boss.transform.parent = GameObject.Find ("Boss").transform;
		obj_boss.transform.localScale = new Vector3(420.0f, 610.0f, 0.0f);
		obj_boss.gameObject.SetActive(false);

		Move ();
	}
	
	void FixedUpdate ()
	{
		
	}
	
	public override void Move ()
	{
		StartCoroutine ("Make_Image");
	}
	
	IEnumerator Make_Image()
	{
		obj_boss.gameObject.SetActive(true);
		yield return new WaitForSeconds(3.0f);

		for( int i = 0; i < 10; ++i )
		{
			//Instantiate (Resources.Load (prefab[0],
			 //            new Vector3(390.0f, 20.0f, 0.0f), Quaternion.identity)) as Transform;
			yield return new WaitForSeconds(0.1f);
	    }
		for( int i = 0; i < 10; ++i )
		{
			//Instantiate (Resources.Load (prefab[1],
			//	         new Vector3(390.0f, 20.0f, 0.0f), Quaternion.identity)) as Transform;
			yield return new WaitForSeconds(0.1f);
		}
		yield return new WaitForSeconds(2.0f);
		
		end_check = true;
	}
}