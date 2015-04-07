using UnityEngine;
using System.Collections;

public class Pattern1_3 : Pattern_State
{
	private GameObject[] obj_warning = new GameObject[4];
	private GameObject[] obj_caution = new GameObject[8];
	public AudioClip _sound;
	public bool end_check;

	void Start ()
	{
		end_check = false;

		for( int i = 0; i < 4; ++i )
		{
			obj_warning[i] = Instantiate (Resources.Load ("Boss1_4", typeof(GameObject))) as GameObject;
			obj_warning[i].transform.parent = GameObject.Find ("Boss").transform;
			obj_warning[i].transform.localScale = new Vector3(150.0f, 220.0f, 0.0f);
			obj_warning[i].gameObject.SetActive(false);
		}

		// caution
		for( int i = 0; i < 8; ++i )
		{
			if( i < 4 )
			{
				obj_caution[i] = Instantiate (Resources.Load ("Warning_back", typeof(GameObject))) as GameObject;
				obj_caution[i].transform.parent = GameObject.Find ("Boss").transform;
				obj_caution[i].transform.localScale = new Vector3(150.0f, 720.0f, 0.0f);
				obj_caution[i].gameObject.SetActive(false);
			}
			else
			{
				obj_caution[i] = Instantiate (Resources.Load ("Warning_guide", typeof(GameObject))) as GameObject;
				obj_caution[i].transform.parent = GameObject.Find ("Boss").transform;
				obj_caution[i].transform.localScale = new Vector3(80.0f, 80.0f, 0.0f);
				obj_caution[i].gameObject.SetActive(false);
			}
		}

		Move ();
	}

	void FixedUpdate ()
	{

	}

	public override void Move ()
	{
		for (int i = 0; i < 8; ++i)
			StartCoroutine ("Register_Time");
	}
	
	IEnumerator Register_Time()
	{
		GetComponent<AudioSource> ().clip = _sound;
		GetComponent<AudioSource> ().Play ();
		yield return new WaitForSeconds (2.2f);

		for( int i = 0; i < 8; ++i )
		{
			if( i < 4 )
			{
				obj_caution[i].transform.localPosition = new Vector3(-450.0f + ((float)i*300.0f), 0.0f, 0.0f);
			}
			else
			{
				obj_caution[i].transform.localPosition = new Vector3(-450.0f + (((float)i-4)*300.0f), 0.0f, 0.0f);
			}
			obj_caution[i].SetActive(true);
		}
		yield return new WaitForSeconds (0.5f);

		for( int i = 0; i < 8; ++i )
		{
			DestroyObject(obj_caution[i]);
		}
		yield return new WaitForSeconds (0.3f);

		for (int i = 0; i < 4; ++i)
		{
			obj_warning[i].transform.localPosition = new Vector3 (-450.0f + ((float)i * 300.0f), -210.0f, 0.0f);
			obj_warning[i].SetActive(true);
		}
		yield return new WaitForSeconds (2.2f);

		for (int i = 0; i < 4; ++i)
		{
			obj_warning[i].GetComponent<Enemy1_3>().Left_Sound();
			obj_warning [i].GetComponent<Enemy1_3> ().dir = false;
			obj_warning [i].GetComponent<Enemy1_3> ().move = true;
		}
		yield return new WaitForSeconds (2.5f);
		
		for (int i = 0; i < 4; ++i)
		{
			obj_warning[i].GetComponent<Enemy1_3>().Right_Sound();
			obj_warning [i].GetComponent<Enemy1_3> ().dir = true;
		}
		yield return new WaitForSeconds (2.0f);

		for (int i = 0; i < 4; ++i)
		{
			obj_warning[i].GetComponent<Enemy1_3>().Stop_Sound();
			obj_warning [i].GetComponent<Enemy1_3> ().move = false;
		}
		yield return new WaitForSeconds (1.1f);

		for (int i = 0; i < 4; ++i)
		{
			obj_warning[i].GetComponent<Enemy1_3>().Final_Sound();
			// dir
			if (i < 2)
				obj_warning [i].GetComponent<Enemy1_3> ().dir = false;
			else
				obj_warning [i].GetComponent<Enemy1_3> ().dir = true;

			// move check
			obj_warning [i].GetComponent<Enemy1_3> ().move = true;

			// Speed
			obj_warning [i].GetComponent<Enemy1_3> ().moveSpeed = 400.0f / 1.0f;
		}
		yield return new WaitForSeconds (2.0f);

		for (int i = 0; i < 4; ++i)
			DestroyObject (obj_warning [i]);

		end_check = true;
	}
}