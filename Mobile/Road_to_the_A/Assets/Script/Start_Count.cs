using UnityEngine;
using System.Collections;

public class Start_Count : MonoBehaviour
{
	public AudioClip[] _sound = new AudioClip[2];

	// Image
	private UISprite sprite;
	static public bool start_check;

	// Count

	void Start()
	{
		start_check = false;
		sprite = gameObject.GetComponent<UISprite>();

		StartCoroutine ("Change_Image");
	}

	IEnumerator Change_Image()
	{
		sprite.spriteName = "play_c_1";
		GetComponent<AudioSource> ().clip = _sound[0];
		GetComponent<AudioSource> ().Play ();
		yield return new WaitForSeconds(1);

		sprite.spriteName = "play_c_2";
		GetComponent<AudioSource> ().clip = _sound[0];
		GetComponent<AudioSource> ().Play ();
		yield return new WaitForSeconds(1);

		sprite.spriteName = "play_c_3";
		GetComponent<AudioSource> ().clip = _sound[0];
		GetComponent<AudioSource> ().Play ();
		yield return new WaitForSeconds(1);

		sprite.transform.localScale = new Vector3 (520.0f, 160.0f, 0.0f);
		sprite.spriteName = "play_c_s";
		GetComponent<AudioSource> ().clip = _sound[1];
		GetComponent<AudioSource> ().Play ();
		Move_Character.m_move = true;
		start_check = true;
		yield return new WaitForSeconds(1);

		Destroy(gameObject);
		yield return new WaitForSeconds(1);
	}
}