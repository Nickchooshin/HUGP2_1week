using UnityEngine;
using System.Collections;

public class Pattern6_2 : Pattern_State
{
	private GameObject obj_warning;
	private GameObject[] obj_caution = new GameObject[2];
	public AudioClip _sound;
	
	public bool end_check;

	void Start ()
	{
		end_check = false;

		// warning
		obj_warning = Instantiate (Resources.Load ("Boss6_4", typeof(GameObject))) as GameObject;
		obj_warning.transform.parent = GameObject.Find ("Boss").transform;
		obj_warning.transform.localScale = new Vector3(300.0f, 450.0f, 0.0f);
		obj_warning.gameObject.SetActive(false);

		// caution
		obj_caution[0] = Instantiate (Resources.Load ("Warning_back", typeof(GameObject))) as GameObject;
		obj_caution[0].transform.parent = GameObject.Find ("Boss").transform;
		obj_caution[0].transform.localScale = new Vector3(300.0f, 720.0f, 0.0f);
		obj_caution[0].gameObject.SetActive(false);
		
		obj_caution[1] = Instantiate (Resources.Load ("Warning_guide", typeof(GameObject))) as GameObject;
		obj_caution[1].transform.parent = GameObject.Find ("Boss").transform;
		obj_caution[1].transform.localScale = new Vector3(200.0f, 200.0f, 0.0f);
		obj_caution[1].gameObject.SetActive(false);

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
		// Audio
		GetComponent<AudioSource> ().clip = _sound;
		GetComponent<AudioSource> ().Play ();
		yield return new WaitForSeconds(2.0f);

		for( int i = 0; i < 2; ++i )
		{
			obj_caution[i].GetComponent<Warning> ().chase_check = true;
			obj_caution[i].gameObject.SetActive(true);
		}
		yield return new WaitForSeconds(1.8f);

		for (int i = 0; i < 2; ++i)
			obj_caution[i].gameObject.SetActive(false);
		yield return new WaitForSeconds(0.2f);

		obj_warning.transform.localPosition =
			new Vector3(obj_caution[0].transform.localPosition.x, 585.0f, 0.0f);
		obj_warning.gameObject.SetActive(true);
		yield return new WaitForSeconds(2.0f);
		
		end_check = true;
	}
}