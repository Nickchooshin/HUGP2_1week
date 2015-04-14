using UnityEngine;
using System.Collections;

public class Pattern5_1 : Pattern_State
{
	private GameObject obj_safe;
	private GameObject[] obj_caution = new GameObject[2];
	private GameObject[] obj_warning = new GameObject[27];
	public AudioClip[] _sound = new AudioClip[3];
	
	public bool end_check;
	
	void Start ()
	{
		end_check = false;
		
		// safe
		obj_safe = Instantiate (Resources.Load ("Boss5_1", typeof(GameObject))) as GameObject;
		obj_safe.transform.parent = GameObject.Find ("Boss").transform;
		obj_safe.transform.localScale = new Vector3(450.0f, 600.0f, 0.0f);
		obj_safe.gameObject.SetActive(false);

		// caution
		obj_caution[0] = Instantiate (Resources.Load ("Warning_back", typeof(GameObject))) as GameObject;
		obj_caution[0].transform.parent = GameObject.Find ("Boss").transform;
		obj_caution[0].transform.localScale = new Vector3(1280.0f, 100.0f, 0.0f);
		obj_caution[0].gameObject.SetActive(false);
		
		obj_caution[1] = Instantiate (Resources.Load ("Warning_guide", typeof(GameObject))) as GameObject;
		obj_caution[1].transform.parent = GameObject.Find ("Boss").transform;
		obj_caution[1].transform.localScale = new Vector3(80.0f, 80.0f, 0.0f);
		obj_caution[1].gameObject.SetActive(false);
		
		for( int i = 0; i < 27; ++i )
		{
			obj_warning[i] = Instantiate (Resources.Load ("Boss5_2", typeof(GameObject))) as GameObject;
			obj_warning[i].transform.parent = GameObject.Find ("Boss").transform;
			obj_warning[i].transform.localScale = new Vector3(50.0f, 50.0f, 0.0f);
			obj_warning[i].gameObject.SetActive(false);

			if( 26 == i )
			{
				obj_warning[i] = Instantiate (Resources.Load ("Boss5_3", typeof(GameObject))) as GameObject;
				obj_warning[i].transform.parent = GameObject.Find ("Boss").transform;
				obj_warning[i].transform.localScale = new Vector3(1280.0f, 100.0f, 0.0f);
				obj_warning[i].gameObject.SetActive(false);
			}
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
		obj_safe.transform.localPosition = new Vector3 (840.0f, 0.0f, 0.0f);
		obj_safe.gameObject.SetActive(true);
		yield return new WaitForSeconds(3.5f);

		for (int i = 0; i < 2; ++i)
		{
			obj_caution[i].transform.localPosition = new Vector3(0.0f, -280.0f, 0.0f);
			obj_caution [i].SetActive (true);
		}
		yield return new WaitForSeconds(0.5f);

		for (int i = 0; i < 13; ++i)
		{
			obj_warning[i].transform.localPosition =
				new Vector3(-615.0f + (i * 100.0f), 380.0f, 0.0f);
			obj_warning [i].SetActive (true);
		}
		yield return new WaitForSeconds(0.5f);

		for( int i = 0; i < 2; ++i )
			DestroyObject (obj_caution [i]);
		for (int i = 13; i < 26; ++i)
		{
			obj_warning[i].transform.localPosition =
				new Vector3(-565.0f + ((i-13) * 100.0f), 380.0f, 0.0f);
			obj_warning [i].SetActive (true);
		}
		yield return new WaitForSeconds(0.5f);

		obj_warning[26].transform.localPosition =
			new Vector3(0.0f, -410.0f, 0.0f);
		obj_warning[26].SetActive (true);
		yield return new WaitForSeconds(1.0f);
		
		DestroyObject (obj_safe);
		for (int i = 0; i < 27; ++i)
			DestroyObject (obj_warning [i]);

		end_check = true;
	}
}