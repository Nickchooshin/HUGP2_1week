using UnityEngine;
using System.Collections;

public class Pattern3_3 : Pattern_State
{
	public AudioClip _sound;

	private GameObject[] obj_warning = new GameObject[5];
	private GameObject[] obj_caution = new GameObject[2];

	public bool end_check;
	
	void Start ()
	{
		end_check = false;

		// caution
		obj_caution[0] = Instantiate (Resources.Load ("Warning_back", typeof(GameObject))) as GameObject;
		obj_caution[0].transform.parent = GameObject.Find ("Boss").transform;
		obj_caution[0].transform.localScale = new Vector3(100.0f, 720.0f, 0.0f);
		obj_caution[0].gameObject.SetActive(false);

		obj_caution[1] = Instantiate (Resources.Load ("Warning_guide", typeof(GameObject))) as GameObject;
		obj_caution[1].transform.parent = GameObject.Find ("Boss").transform;
		obj_caution[1].transform.localScale = new Vector3(80.0f, 80.0f, 0.0f);
		obj_caution[1].gameObject.SetActive(false);

		// warning
		for( int i = 0; i < 5; ++i )
		{
			obj_warning[i] = Instantiate (Resources.Load ("Boss3_6", typeof(GameObject))) as GameObject;
			obj_warning[i].transform.parent = GameObject.Find ("Boss").transform;
			obj_warning[i].transform.localScale = new Vector3(100.0f, 148.0f, 0.0f);
			obj_warning[i].gameObject.SetActive(false);
		}
		
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
		GetComponent<AudioSource> ().clip = _sound;
		GetComponent<AudioSource> ().Play ();
		yield return new WaitForSeconds(1.5f);

		for( int i = 0; i < 4; ++i )
		{
			// caution
			for( int j = 0; j < 2; ++j )
			{
				obj_caution[j].gameObject.SetActive(true);
				obj_caution[j].GetComponent<Warning> ().chase_check = true;
			}
			yield return new WaitForSeconds(0.3f);

			// false caution
			for( int j = 0; j < 2; ++j )
				obj_caution[j].gameObject.SetActive(false);
			yield return new WaitForSeconds(0.2f);

			// Make enemy
			obj_warning[i].gameObject.SetActive (true);
			obj_warning[i].transform.localPosition =
				new Vector3(obj_caution[0].transform.localPosition.x, -450.0f, 0.0f);
		}

		// caution
		for( int i = 0; i < 2; ++i )
		{
			obj_caution[i].gameObject.SetActive(true);
			obj_caution[i].GetComponent<Warning> ().chase_check = false;
			obj_caution[i].transform.localPosition = new Vector3(0.0f, -310.0f, 0.0f);

			if( 0 == i )
				obj_caution[i].transform.localScale = new Vector3(1280.0f, 100.0f, 0.0f);
			else
				obj_caution[i].transform.localScale = new Vector3(80.0f, 80.0f, 0.0f);
		}
		yield return new WaitForSeconds(0.2f);

		for (int i = 0; i < 2; ++i)
			obj_caution [i].SetActive (false);

		obj_warning[4].transform.localPosition = new Vector3(-680.0f, -310.0f, 0.0f);
		obj_warning[4].GetComponent<Enemy3_3> ().move_dir = true;
		obj_warning[4].SetActive (true);
		yield return new WaitForSeconds(4.0f);

		for (int i = 0; i < 2; ++i)
			DestroyObject (obj_caution [i]);
		for (int i = 0; i < 5; ++i)
			DestroyObject (obj_warning [i]);
		
		end_check = true;
	}
}