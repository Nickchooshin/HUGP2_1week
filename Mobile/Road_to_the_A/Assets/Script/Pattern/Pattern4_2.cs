using UnityEngine;
using System.Collections;

public class Pattern4_2 : Pattern_State
{
	public AudioClip _sound;

	private GameObject obj_boss;
	private GameObject[] obj_warning = new GameObject[25];
	public Transform[] prefab = new Transform[2];
	
	public bool end_check;
	
	void Start ()
	{
		end_check = false;

		obj_boss = Instantiate (Resources.Load ("Boss4_4", typeof(GameObject))) as GameObject;
		obj_boss.transform.parent = GameObject.Find ("Boss").transform;
		obj_boss.transform.localScale = new Vector3(440.0f, 600.0f, 0.0f);
		obj_boss.gameObject.SetActive(false);

		for( int i = 0; i < 25; ++i )
		{
			if( i > 9 && i < 20 )
				obj_warning[i] = Instantiate (Resources.Load ("Boss4_6", typeof(GameObject))) as GameObject;
			else
				obj_warning[i] = Instantiate (Resources.Load ("Boss4_5", typeof(GameObject))) as GameObject;
			obj_warning[i].transform.parent = GameObject.Find ("Boss").transform;
			obj_warning[i].transform.localScale = new Vector3(40.0f, 40.0f, 0.0f);
			obj_warning[i].gameObject.SetActive(false);
		}

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
		// Audio
		GetComponent<AudioSource> ().clip = _sound;
		GetComponent<AudioSource> ().Play ();

		// Move
		obj_boss.transform.localPosition = new Vector3 (420.0f, 20.0f, 0.0f);
		obj_boss.gameObject.SetActive(true);
		yield return new WaitForSeconds(3.0f);

		for( int i = 0; i < 25; ++i )
		{
			obj_warning[i].GetComponent<Enemy4_2>().move_check = true;
			obj_warning[i].transform.localPosition = new Vector3(390.0f, 110.0f, 0.0f);
			if( i > 9 && i < 20 )
			{
				if( 0 == i % 2 )
				{
					obj_warning[i].GetComponent<Enemy4_2>().dir_num = 3;
				}
				else
				{
					obj_warning[i].GetComponent<Enemy4_2>().dir_num = 4;
				}
			}
			else
			{
				if( 0 == i % 3 )
				{
					obj_warning[i].GetComponent<Enemy4_2>().dir_num = 0;
				}
				else if( 1 == i % 3 )
				{
					obj_warning[i].GetComponent<Enemy4_2>().dir_num = 1;
				}
				else if( 2 == i % 3 )
				{
					obj_warning[i].GetComponent<Enemy4_2>().dir_num = 2;
				}
			}
			obj_warning[i].SetActive(true);
			yield return new WaitForSeconds(0.1f);
	    }
		yield return new WaitForSeconds(1.0f);

		DestroyObject (obj_boss);
		for (int i = 0; i < 25; ++i)
			DestroyObject (obj_warning [i]);
		end_check = true;
	}
}