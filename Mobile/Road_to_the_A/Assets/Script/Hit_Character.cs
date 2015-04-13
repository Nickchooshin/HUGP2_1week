using UnityEngine;
using System.Collections;

public class Hit_Character : MonoBehaviour
{
	void OnCollisionEnter2D( Collision2D other )
	{
		if( "Enemy" == other.collider.tag )
			Move_Character.m_dead = true;
	}
	
	void OnTriggerEnter2D( Collider2D other )
	{
		if( "Enemy" == other.tag )
			Move_Character.m_dead = true;
	}
	
	void End_Game()
	{
		if( true == Move_Character.m_dead )
		{
			Application.LoadLevel ("End");
		}
	}
}