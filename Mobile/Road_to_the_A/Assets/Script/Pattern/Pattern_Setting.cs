using UnityEngine;
using System.Collections;

public class Pattern_Setting : MonoBehaviour
{
	// Image
	static public void Image_SetPos( GameObject _obj, Vector3 _pos )
	{
		// Position setting
		_obj.transform.localPosition = _pos;
	}

	// Sound
	static public void Sound_Play()
	{

	}
}