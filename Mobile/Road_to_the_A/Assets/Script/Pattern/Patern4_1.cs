using UnityEngine;
using System.Collections;

public class Patern4_1 : Pattern_State
{
	private GameObject[] obj_safe = new GameObject[2];
	private GameObject[] obj_warning = new GameObject[4];
	public AudioClip[] _sound = new AudioClip[3];
	
	void Start ()
	{
		// safe
		obj_safe[0] = Instantiate (Resources.Load ("Boss4_1", typeof(GameObject))) as GameObject;
		obj_safe[0].transform.parent = GameObject.Find ("Boss").transform;
		obj_safe[0].transform.localScale = new Vector3(580.0f, 600.0f, 0.0f);
		obj_safe[0].gameObject.SetActive(false);

		obj_safe[1] = Instantiate (Resources.Load ("Boss4_2", typeof(GameObject))) as GameObject;
		obj_safe[1].transform.parent = GameObject.Find ("Boss").transform;
		obj_safe[1].transform.localScale = new Vector3(90.0f, 640.0f, 0.0f);
		obj_safe[1].gameObject.SetActive(false);

		for( int i = 0; i < 4; ++i )
		{
			obj_warning[i] = Instantiate (Resources.Load ("Boss4_3", typeof(GameObject))) as GameObject;
			obj_warning[i].transform.parent = GameObject.Find ("Boss").transform;
			obj_warning[i].transform.localScale = new Vector3(250.0f, 40.0f, 0.0f);
			obj_warning[i].gameObject.SetActive(false);
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
		obj_safe[0].transform.localPosition = new Vector3 (0.0f, 20.0f, 0.0f);
		obj_safe[0].SetActive (true);
		yield return new WaitForSeconds(2.5f);

		obj_safe[0].GetComponent<Safe4_1> ().move_check = true;
		yield return new WaitForSeconds(1.8f);

		for( int i = 0; i < 4; ++i )
		{
			if( i < 3 )
			{
				GetComponent<AudioSource> ().clip = _sound[i];
				GetComponent<AudioSource> ().Play ();
				yield return new WaitForSeconds(1.0f);
			}

			obj_safe[1].GetComponent<Safe4_2> ().tri_check = true;
			if( i == 0 )
			{
				obj_safe[1].transform.localPosition = new Vector3 (560.0f, 680.0f, 0.0f);
				obj_safe[1].SetActive (true);
				yield return new WaitForSeconds(1.3f);
			}
			else
			{
				obj_safe[1].transform.localPosition = new Vector3 (560.0f, 60.0f, 0.0f);
				obj_safe[1].SetActive (true);
				yield return new WaitForSeconds(1.3f);
			}
		
			obj_warning[i].transform.localPosition = new Vector3 (510.0f, -290.0f, 0.0f);
			obj_warning[i].SetActive (true);
			if( i < 3 )
				yield return new WaitForSeconds(0.2f);
			else
				yield return new WaitForSeconds(1.2f);
		}

		yield return new WaitForSeconds(2.0f);

		for (int i = 0; i < 4; ++i)
			DestroyObject (obj_warning[i]);
		for (int i = 0; i < 2; ++i)
			DestroyObject (obj_safe[i]);
	}
}