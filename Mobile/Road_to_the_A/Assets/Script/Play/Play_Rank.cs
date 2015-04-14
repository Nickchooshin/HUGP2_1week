using UnityEngine;
using System.Collections;

public class Play_Rank : MonoBehaviour
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
		ScoreManager.getInstance().Grade_pScreen (_sprite);
	}
}