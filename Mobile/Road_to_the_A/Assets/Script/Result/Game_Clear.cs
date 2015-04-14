using UnityEngine;
using System.Collections;

public class Game_Clear : MonoBehaviour
{
	UISprite _sprite;
	
	void Start ()
	{
		_sprite = GetComponent<UISprite> ();
	}
	
	void FixedUpdate()
	{
		Rank ();
	}
	
	void Rank()
	{
		ScoreManager.getInstance().Clear_Screen (_sprite);
	}
}