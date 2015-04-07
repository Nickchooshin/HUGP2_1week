using UnityEngine;
using System.Collections;

public class Start_Count : MonoBehaviour
{
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
		sprite.spriteName = "3";
		yield return new WaitForSeconds(1);

		sprite.spriteName = "2";
		yield return new WaitForSeconds(1);

		sprite.spriteName = "1";
		yield return new WaitForSeconds(1);

		sprite.spriteName = "0";
		Move_Character.m_move = true;
		start_check = true;
		yield return new WaitForSeconds(1);

		Destroy(gameObject);
		yield return new WaitForSeconds(1);
	}
}