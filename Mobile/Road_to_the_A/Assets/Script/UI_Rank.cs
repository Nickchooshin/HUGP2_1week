using UnityEngine;
using System.Collections;

public class UI_Rank : MonoBehaviour
{
	void Start ()
	{
		gameObject.SetActive (false);
	}

	void FixedUpdate ()
	{
		StartCoroutine ("Visible_Image");
	}

	IEnumerator Visible_Image()
	{
		yield return new WaitForSeconds (3.0f);
		gameObject.SetActive (true);
	}
}