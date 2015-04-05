using UnityEngine;
using System.Collections;

public class Pattern3_3 : Pattern_State
{
	public AudioClip _sound;

	private GameObject[] obj_warning = new GameObject[4];
	private GameObject[] obj_caution = new GameObject[2];
	
	void Start ()
	{
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
		for( int i = 0; i < 4; ++i )
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

		for( int i = 0; i < 2; ++i )
		{
			obj_caution[i].gameObject.SetActive(true);
			obj_caution[i].GetComponent<Warning> ().chase_check = true;
		}
		yield return new WaitForSeconds(0.3f);

		for( int i = 0; i < 2; ++i )
			obj_caution[i].gameObject.SetActive(false);
		yield return new WaitForSeconds(0.2f);

		obj_warning[0].gameObject.SetActive (true);
		obj_warning[0].transform.localPosition =
			new Vector3(obj_caution[0].transform.localPosition.x, 500.0f, 0.0f);

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