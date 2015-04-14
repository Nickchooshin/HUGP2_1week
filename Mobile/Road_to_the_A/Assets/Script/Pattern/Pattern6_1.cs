using UnityEngine;
using System.Collections;

public class Pattern6_1 : Pattern_State
{
	private GameObject obj_safe;
	private GameObject[] obj_warning = new GameObject[3];
	public AudioClip[] _sound = new AudioClip[5];

	public bool end_check;

	void Start ()
	{
		end_check = false;

		obj_safe = Instantiate (Resources.Load ("Boss6_1", typeof(GameObject))) as GameObject;
		obj_safe.transform.parent = GameObject.Find ("Boss").transform;
		obj_safe.transform.localScale = new Vector3(720.0f, 550.0f, 0.0f);
		obj_safe.gameObject.SetActive(false);

		for( int i = 0; i < 3; ++i )
		{
			if( 0 == i )
			{
				obj_warning[i] = Instantiate (Resources.Load ("Boss6_2", typeof(GameObject))) as GameObject;
				obj_warning[i].transform.parent = GameObject.Find ("Boss").transform;
				obj_warning[i].transform.localScale = new Vector3(70.0f, 110.0f, 0.0f);
				obj_warning[i].gameObject.SetActive(false);
			}
			else
			{
				obj_warning[i] = Instantiate (Resources.Load ("Boss6_3", typeof(GameObject))) as GameObject;
				obj_warning[i].transform.parent = GameObject.Find ("Boss").transform;
				obj_warning[i].transform.localScale = new Vector3(70.0f, 110.0f, 0.0f);
				obj_warning[i].gameObject.SetActive(false);
			}
		}

		Move();
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
		GetComponent<AudioSource> ().clip = _sound[0];
		GetComponent<AudioSource> ().volume = 0.1f;
		GetComponent<AudioSource> ().Play ();
		// Move
		obj_safe.transform.localPosition = new Vector3(0.0f, -635.0f, 0.0f);
		obj_safe.SetActive (true);
		yield return new WaitForSeconds(2.0f);

		GetComponent<AudioSource> ().clip = _sound[1];
		GetComponent<AudioSource> ().Play ();
		yield return new WaitForSeconds(2.0f);
		
		// Audio
		GetComponent<AudioSource> ().clip = _sound[0];
		GetComponent<AudioSource> ().Play ();
		// Move
		obj_warning[0].transform.localPosition = new Vector3(0.0f, 410.0f, 0.0f);
		obj_warning[0].SetActive (true);
		yield return new WaitForSeconds(2.5f);

		GetComponent<AudioSource> ().clip = _sound[2];
		GetComponent<AudioSource> ().Play ();
		yield return new WaitForSeconds(1.5f);

		for( int i = 1; i < 3; ++i )
		{
			if( 1 == i )
			{
				obj_warning[i].transform.localPosition = new Vector3(-570.0f, -240.0f, 0.0f);
				obj_warning [i].GetComponent<Enemy6_1> ().dir_check = true;
			}
			else
			{
				obj_warning[i].transform.localPosition = new Vector3(570.0f, -240.0f, 0.0f);
				obj_warning [i].GetComponent<Enemy6_1> ().dir_check = false;
			}

			obj_warning[i].SetActive (true);
		}
		yield return new WaitForSeconds(2.0f);

		// Audio
		GetComponent<AudioSource> ().clip = _sound[3];
		GetComponent<AudioSource> ().Play ();
		// Move - Speed up
		for (int i = 1; i < 3; ++i)
			obj_warning [i].GetComponent<Enemy6_1> ().moveSpeed = 500.0f / 1.0f;
		yield return new WaitForSeconds(2.0f);

		// Audio
		GetComponent<AudioSource> ().clip = _sound[4];
		GetComponent<AudioSource> ().Play ();
		// Move - speed up
		for (int i = 1; i < 3; ++i)
			obj_warning [i].GetComponent<Enemy6_1> ().moveSpeed = 600.0f / 1.0f;
		yield return new WaitForSeconds(2.0f);
		
		end_check = true;
	}
}