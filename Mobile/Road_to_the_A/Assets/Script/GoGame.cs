using UnityEngine;
using System.Collections;

public class GoGame : MonoBehaviour
{
	void Go_Game()
	{
		Next.next = true;

		if (null != ScoreManager.getInstance())
			Destroy (ScoreManager.getInstance ());

		Application.LoadLevel ("Game");
	}
}