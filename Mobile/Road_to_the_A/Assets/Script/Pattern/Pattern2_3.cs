using UnityEngine;
using System.Collections;

public class Pattern2_3 : Pattern_State
{
	public AudioClip _sound;

	private GameObject[] obj_warning = new GameObject[5];

	void Start ()
	{
		for( int i = 0; i < 5; ++i )
		{
			// Enemy
			obj_warning[i] = Instantiate (Resources.Load ("Boss2_5", typeof(GameObject))) as GameObject;
			obj_warning[i].transform.parent = GameObject.Find ("Boss").transform;
			obj_warning[i].transform.localScale = new Vector3(190.0f, 110.0f, 0.0f);
			obj_warning[i].gameObject.SetActive(false);
		}

		// Enemy Position
		obj_warning[0].transform.localPosition = new Vector3(-500.0f, 280.0f, 0.0f);
		obj_warning[1].transform.localPosition = new Vector3(500.0f, -240.0f, 0.0f);
		obj_warning[2].transform.localPosition = new Vector3(500.0f, 280.0f, 0.0f);
		obj_warning[3].transform.localPosition = new Vector3(-500.0f, -240.0f, 0.0f);
		obj_warning[4].transform.localPosition = new Vector3(0.0f, 280.0f, 0.0f);

		Move ();
	}

	void FixedUpdate ()
	{
		
	}

	public override void Move ()
	{
		StartCoroutine ("Change_Image");
	}

	IEnumerator Change_Image()
	{
		GetComponent<AudioSource> ().clip = _sound;
		GetComponent<AudioSource> ().Play ();
		yield return new WaitForSeconds(2.5f);

		for (int i = 0; i < 5; ++i)
			obj_warning [i].SetActive (true);
		yield return new WaitForSeconds(0.5f);

		for( int i = 0; i < 4; ++i )
		{
			obj_warning [i].GetComponent<Enemy2_3> ().move_check = true;

			if( i < 3 )
				yield return new WaitForSeconds(1.0f);
			else
				yield return new WaitForSeconds(0.5f);
		}

		obj_warning[4].GetComponent<Enemy2_3> ().move_check = true;
		yield return new WaitForSeconds(1.0f);

		for( int i = 0; i < 5; ++i )
			DestroyObject(obj_warning[i]);
	}
}