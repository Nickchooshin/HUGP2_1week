using UnityEngine;
using System.Collections;

public class Pattern2_2 : Pattern_State
{
	private GameObject[] obj_warning = new GameObject[20];
	private GameObject obj_caution;
	private bool check;
	public AudioClip _sound;
	
	void Start ()
	{
		for( int i = 0; i < 20; ++i )
		{
			// Enemy
			obj_warning[i] = Instantiate (Resources.Load ("Boss2_4", typeof(GameObject))) as GameObject;
			obj_warning[i].transform.parent = GameObject.Find ("Boss").transform;
			obj_warning[i].transform.localScale = new Vector3(Random.Range(150.0f,250.0f), 2.0f, 0.0f);
			obj_warning[i].transform.localPosition =
				new Vector3(Random.Range(-640.0f,640.0f), Random.Range(-360.0f,360.0f), 0.0f);
			obj_warning[i].gameObject.SetActive(false);
		}
		
		// caution
		obj_caution = Instantiate (Resources.Load ("Boss2_3", typeof(GameObject))) as GameObject;
		obj_caution.transform.parent = GameObject.Find ("Boss").transform;
		obj_caution.transform.localScale = new Vector3(80.0f, 720.0f, 0.0f);
		obj_caution.GetComponent<Warning> ().chase_check = true;
		obj_caution.gameObject.SetActive(false);
		
		check = false;
		Move ();
	}
	
	void FixedUpdate ()
	{
		if (true == check)
			Deadzone ();
	}

	void Deadzone()
	{
		for (int i = 0; i < 20; ++i)
			obj_warning [i].SetActive (true);

		if( (obj_caution.transform.localPosition.x - 40.0f) >
		   GameObject.FindGameObjectWithTag("Player").transform.localPosition.x ||
		   (obj_caution.transform.localPosition.x + 40.0f) <
		   GameObject.FindGameObjectWithTag("Player").transform.localPosition.x )
			Application.LoadLevel ("End");
	}
	
	public override void Move ()
	{
		StartCoroutine ("Change_Image");
	}
	
	public IEnumerator Change_Image()
	{
		GetComponent<AudioSource> ().clip = _sound;
		GetComponent<AudioSource> ().Play ();
		yield return new WaitForSeconds(2.0f);

		obj_caution.SetActive (true);
		yield return new WaitForSeconds(0.5f);

		obj_caution.SetActive (false);
		yield return new WaitForSeconds(0.2f);

		check = true;
		yield return new WaitForSeconds(3.0f);

		check = false;
		DestroyObject (obj_caution);
		for (int i = 0; i < 20; ++i)
			DestroyObject (obj_warning[i]);
	}
}