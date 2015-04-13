using UnityEngine;
using System.Collections;

public class Pattern5_2 : Pattern_State
{
	private GameObject[] obj_caution = new GameObject[2];
	private GameObject obj_warning;
	public AudioClip _sound;
	
	public bool end_check;
	
	void Start ()
	{
		end_check = false;

		// caution
		obj_caution[0] = Instantiate (Resources.Load ("Warning_back", typeof(GameObject))) as GameObject;
		obj_caution[0].transform.parent = GameObject.Find ("Boss").transform;
		obj_caution[0].transform.localScale = new Vector3(600.0f, 720.0f, 0.0f);
		obj_caution[0].gameObject.SetActive(false);
		
		obj_caution[1] = Instantiate (Resources.Load ("Warning_guide", typeof(GameObject))) as GameObject;
		obj_caution[1].transform.parent = GameObject.Find ("Boss").transform;
		obj_caution[1].transform.localScale = new Vector3(300.0f, 300.0f, 0.0f);
		obj_caution[1].gameObject.SetActive(false);

		// warning
		obj_warning = Instantiate (Resources.Load ("Boss5_4", typeof(GameObject))) as GameObject;
		obj_warning.transform.parent = GameObject.Find ("Boss").transform;
		obj_warning.transform.localScale = new Vector3(560.0f, 600.0f, 0.0f);
		obj_warning.gameObject.SetActive(false);

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
		// Audio
		GetComponent<AudioSource> ().clip = _sound;
		GetComponent<AudioSource> ().Play ();

		// Move
		for (int i = 0; i < 2; ++i)
		{
			obj_caution[i].transform.localPosition =
				new Vector3(GameObject.FindGameObjectWithTag ("Player").transform.localPosition.x, 0.0f, 0.0f); 
			obj_caution[i].GetComponent<Warning> ().chaseA_check = true;
			obj_caution[i].SetActive(true);
		}
		yield return new WaitForSeconds(6.0f);

		for (int i = 0; i < 2; ++i)
			obj_caution [i].SetActive (false);
		yield return new WaitForSeconds(0.3f);

		obj_warning.transform.localPosition =
			new Vector3 (obj_caution[0].transform.localPosition.x, 770.0f, 0.0f);
		obj_warning.SetActive (true);
		yield return new WaitForSeconds(2.0f);

		end_check = true;
	}
}
