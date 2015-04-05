using UnityEngine;
using System.Collections;

public class Pattern1_2 : Pattern_State
{
	private GameObject[] obj_warning = new GameObject[9];
	private GameObject[] obj_caution = new GameObject[2];
	public AudioClip _sound;
	
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

		// caution
		obj_caution[0] = Instantiate (Resources.Load ("Warning_back", typeof(GameObject))) as GameObject;
		obj_caution[0].transform.parent = GameObject.Find ("Boss").transform;
		obj_caution[0].transform.localScale = new Vector3(200.0f, 720.0f, 0.0f);
		obj_caution[0].gameObject.SetActive(false);
		
		obj_caution[1] = Instantiate (Resources.Load ("Warning_guide", typeof(GameObject))) as GameObject;
		obj_caution[1].transform.parent = GameObject.Find ("Boss").transform;
		obj_caution[1].transform.localScale = new Vector3(120.0f, 120.0f, 0.0f);
		obj_caution[1].gameObject.SetActive(false);

		//GetComponent<AudioSource> ().clip = _sound;
		//GetComponent<AudioSource> ().Play ();

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
		yield return new WaitForSeconds(3.2f);

		for( int i = 0; i < 2; ++i )
			obj_caution[i].gameObject.SetActive(true);

		for( int i = 0; i < 3; ++i )
		{
			obj_caution[0].transform.localPosition = new Vector3(-500.0f + ((float)i*400.0f), 0.0f, 0.0f);
			obj_caution[1].transform.localPosition = new Vector3(-500.0f + ((float)i*400.0f), 0.0f, 0.0f);
			yield return new WaitForSeconds(0.5f);
		}

		for( int i = 0; i < 2; ++i )
			DestroyObject (obj_caution[i]);
		yield return new WaitForSeconds(0.3f);

		for( int i = 0; i < 3; ++i )
		{
			obj_warning[i].transform.localPosition = new Vector3(-500.0f + ((float)i * 400.0f), 510.0f, 0.0f);
			obj_warning[i].gameObject.SetActive(true);
		}
		yield return new WaitForSeconds(0.3f);

		for( int i = 3; i < 6; ++i )
		{
			obj_warning[i].transform.localPosition = new Vector3(-500.0f + (((float)i-3) * 400.0f), 510.0f, 0.0f);
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
			obj_warning[i].transform.localPosition = new Vector3(-500.0f + (((float)i-6) * 400.0f), 510.0f, 0.0f);
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