using UnityEngine;
using System.Collections;

public class ScoreManager : MonoBehaviour
{
	private static ScoreManager _instance;
	private static GameObject _container;

	float m_time;
	float clear_time;
	float minus_time;

	public int score;
	public bool first;
	public bool game_Clear;

	void Awake ()
	{
		first = false;
		score = 0;
		minus_time = 0.0f;
		clear_time = 116.2f;
		game_Clear = false;
	}

	void Start()
	{
		DontDestroyOnLoad(this);
	}

	void OnDisable()
	{
		_instance = null;
	}
	
	public static ScoreManager getInstance()
	{
		if( null == _instance )
		{
			_container = new GameObject();  
			_container.name = "_Score";
			_instance = _container.AddComponent(typeof(ScoreManager)) as ScoreManager;
			//_instance = GameObject.FindObjectOfType(typeof(ScoreManager));

			return _instance;
		}

		return _instance;
	}

	public void Score_Cal()
	{
		if( true == Start_Count.start_check )
		{
			// 초기설정
			if( false == first )
			{
				score = 0;
				game_Clear = false;
				m_time = Time.time;

				first = true;
			}

			minus_time = Time.time - m_time;
			if( score < 10000 )
				score = (int)(83.0f * minus_time);
			else
			{
				score = 10000;
			}
		}
	}

	public void Grade_pScreen( UISprite _sprite )
	{
		if( score < 1000 )
		{
			_sprite.spriteName = "play_rank_F";
		}
		else if( score < 2000 )
		{
			_sprite.spriteName = "play_rank_D";
		}
		else if( score < 3000 )
		{
			_sprite.spriteName = "play_rank_D+";
		}
		else if( score < 4000 )
		{
			_sprite.spriteName = "play_rank_C";
		}
		else if( score < 5000 )
		{
			_sprite.spriteName = "play_rank_C+";
		}
		else if( score < 6000 )
		{
			_sprite.spriteName = "play_rank_B";
		}
		else if( score < 7300 )
		{
			_sprite.spriteName = "play_rank_B+";
		}
		else if( score < 10000 )
		{
			_sprite.spriteName = "play_rank_A";
		}
		else
		{
			_sprite.spriteName = "play_rank_A+";
		}
	}

	public void Grade_rScreen( UISprite _sprite )
	{
		if( score < 1000 )
		{
			_sprite.spriteName = "rst_rank_F";
		}
		else if( score < 2000 )
		{
			_sprite.spriteName = "rst_rank_D";
		}
		else if( score < 3000 )
		{
			_sprite.spriteName = "rst_rank_D+";
		}
		else if( score < 4000 )
		{
			_sprite.spriteName = "rst_rank_C";
		}
		else if( score < 5000 )
		{
			_sprite.spriteName = "rst_rank_C+";
		}
		else if( score < 6000 )
		{
			_sprite.spriteName = "rst_rank_B";
		}
		else if( score < 7300 )
		{
			_sprite.spriteName = "rst_rank_B+";
		}
		else if( score < 10000 )
		{
			_sprite.spriteName = "rst_rank_A";
		}
		else
		{
			_sprite.spriteName = "rst_rank_A+";
		}
	}

	public void Score_pScreen( UISprite _sprite, int _num )
	{
		switch(_num)
		{
		case 0:
			_sprite.spriteName = "0";
			break;

		case 1:
			_sprite.spriteName = "1";
			break;

		case 2:
			_sprite.spriteName = "2";
			break;

		case 3:
			_sprite.spriteName = "3";
			break;
			
		case 4:
			_sprite.spriteName = "4";
			break;
			
		case 5:
			_sprite.spriteName = "5";
			break;
			
		case 6:
			_sprite.spriteName = "6";
			break;
			
		case 7:
			_sprite.spriteName = "7";
			break;
			
		case 8:
			_sprite.spriteName = "8";
			break;
			
		case 9:
			_sprite.spriteName = "9";
			break;

		default:
			break;
		}
	}

	public void Score_rScreen( UISprite _sprite, int _num )
	{
		switch(_num)
		{
		case 0:
			_sprite.spriteName = "0";
			break;
			
		case 1:
			_sprite.spriteName = "1";
			break;
			
		case 2:
			_sprite.spriteName = "2";
			break;
			
		case 3:
			_sprite.spriteName = "3";
			break;
			
		case 4:
			_sprite.spriteName = "4";
			break;
			
		case 5:
			_sprite.spriteName = "5";
			break;
			
		case 6:
			_sprite.spriteName = "6";
			break;
			
		case 7:
			_sprite.spriteName = "7";
			break;
			
		case 8:
			_sprite.spriteName = "8";
			break;
			
		case 9:
			_sprite.spriteName = "9";
			break;
			
		default:
			break;
		}
	}

	public void Clear_Screen( UISprite _sprite )
	{
		if( false == game_Clear )
			_sprite.spriteName = "rst_txt_over";
		else
			_sprite.spriteName = "rst_txt_clear";
	}
}