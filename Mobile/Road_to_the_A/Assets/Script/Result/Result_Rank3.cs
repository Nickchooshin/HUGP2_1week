using UnityEngine;
using System.Collections;

public class Result_Rank3 : MonoBehaviour
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
		m_score = ScoreManager.getInstance().score % 1000;
		m_score = (int)((float)m_score * 0.01f);
		ScoreManager.getInstance().Score_rScreen (_sprite, m_score);
	}
}
