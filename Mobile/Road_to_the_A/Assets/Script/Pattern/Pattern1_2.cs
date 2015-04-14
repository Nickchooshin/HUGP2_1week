using UnityEngine;
using System.Collections;

public class Pattern1_2 : Pattern_State
{
	private GameObject[] obj_warning = new GameObject[9];
	private GameObject[] obj_caution = new GameObject[12];
	public AudioClip _sound;
	public bool end_check;
	
	void Start () 
	{
		end_check = false;

		// Warning Setting
		for( int i = 0; i < 9; ++i )
		{
			obj_warning[i] = Instantiate (Resources.Load ("Boss1_3", typeof(GameObject))) as GameObject;
			obj_warning[i].transform.parent = GameObject.Find ("Boss").transform;
			obj_warning[i].transform.localScale = new Vector3(200.0f, 300.0f, 0.0f);
			obj_warning[i].gameObject.SetActive(false);
		}

		for( int i = 0; i < 12; ++i )
		{
			if( 0 == i % 2 )
			{
				obj_caution[i] = Instantiate (Resources.Load ("Warning_back", typeof(GameObject))) as GameObject;
				obj_caution[i].transform.parent = GameObject.Find ("Boss").transform;
				obj_caution[i].transform.localScale = new Vector3(200.0f, 720.0f, 0.0f);
				obj_caution[i].gameObject.SetActive(false);
			}
			else
			{
				obj_caution[i] = Instantiate (Resources.Load ("Warning_guide", typeof(GameObject))) as GameObject;
				obj_caution[i].transform.parent = GameObject.Find ("Boss").transform;
				obj_caution[i].transform.localScale = new Vector3(120.0f, 120.0f, 0.0f);
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
		StartCoroutine ("Change_Image");
	}
	
	IEnumerator Change_Image()
	{
		GetComponent<AudioSource> ().clip = _sound;
		GetComponent<AudioSource> ().Play ();
		yield return new WaitForSeconds(3.2f);

		for( int i = 0; i < 2; ++i )
		{
			for( int j = 0 + (i*6); j < 6 + (i*6); ++j )
			{
				if( 0 == i )
				{
					obj_caution[j].transform.localPosition = new Vector3(-500.0f + ((j/2)*400.0f), 0.0f, 0.0f);
				}
				else
				{
					obj_caution[j].transform.localPosition = new Vector3(-300.0f + (((j-6)/2)*400.0f), 0.0f, 0.0f);
				}
			}
		}

		for( int i = 0; i < 2; ++i )
		{
			for( int j = 0 + (i*6); j < 6 + (i*6); ++j )
			{
				if( 1 == i )
				{
					for( int k = 0; k < 6; ++k )
						obj_caution[k].gameObject.SetActive(false);
				}

				obj_caution[j].gameObject.SetActive(true);
			}
			yield return new WaitForSeconds(0.5f);
		}

		for( int i = 0; i < 6 ; ++i )
		{
			for( int j = 6; j < 12; ++j )
			{
				obj_caution[j].gameObject.SetActive(false);
			}
			obj_caution[i].gameObject.SetActive(true);
		}
		yield return new WaitForSeconds(0.5f);

		for( int i = 0; i < 12; ++i )
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
			obj_warning[i].transform.localPosition = new Vector3(-300.0f + (((float)i-3) * 400.0f), 510.0f, 0.0f);
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
		yield return new WaitForSeconds(0.4f);
		
		end_check = true;
	}
}