using UnityEngine;
using System.Collections;

public class Count : MonoBehaviour
{
	// Image
	private UISprite sprite;

	// Count

	void Start()
	{
		sprite = gameObject.GetComponent<UISprite>();

		for ( int num = 0; num < 4; ++num )
		{
			StartCoroutine ("Change_Image");
		}
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
		yield return new WaitForSeconds(1);
	}
}