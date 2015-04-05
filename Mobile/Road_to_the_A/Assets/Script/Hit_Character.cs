using UnityEngine;
using System.Collections;

public class Hit_Character : MonoBehaviour
{
	void OnCollisionEnter2D( Collision2D other )
	{
		if( other.collider.tag == "Enemy" )
			Application.LoadLevel ("End");
	}

	void OnTriggerEnter2D( Collider2D other )
	{
		if( other.tag == "Enemy" )
			Application.LoadLevel ("End");
	}
}