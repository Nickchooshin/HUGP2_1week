using UnityEngine;
using System.Collections;

public class Result_Rank1 : MonoBehaviour
{
	int m_score;
	UISprite _sprite;

	void Start ()
	{
		m_score = 0;
		_sprite = GetComponent<UISprite> ();
	}

	void FixedUpdate()
	{
		Score ();
	}

	void Score()
	{
		m_score = ScoreManager.getInstance().score % 10;
		ScoreManager.getInstance().Score_rScreen (_sprite, m_score);
	}
}