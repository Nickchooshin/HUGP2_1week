using UnityEngine;
using System.Collections;

public class GoMain : MonoBehaviour
{
	void Go_Main()
	{
		Next.next = true;
		Application.LoadLevel ("Main");
	}
}