using UnityEngine;
using System.Collections;

public class Pattern5_2 : Pattern_State
{
	private GameObject[] obj_caution = new GameObject[2];
	private GameObject obj_warning;
	
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
		obj_warning.transform.localScale = new Vector3(580.0f, 600.0f, 0.0f);
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
		for (int i = 0; i < 2; ++i)
			obj_caution [i].GetComponent<Warning> ().chase_check = true;
		yield return new WaitForSeconds(1.2f);

		end_check = true;
	}
}
