using UnityEngine;
using System.Collections;
using System.IO.Ports;

public class DepthGrab : MonoBehaviour {


	public int depthLevel = 0;
	public static SerialPort sp = new SerialPort ("COM3", 9600, Parity.None, 8, StopBits.One);

	// Use this for initialization
	void Start () {
		
		sp.Open ();
		sp.ReadTimeout = 1;
	}
	
	// Update is called once per frame
	void Update () {
		if (sp.IsOpen) {
			byte[] b = System.BitConverter.GetBytes (depthLevel);
			sp.Write (b, 0, 4);
		}
		//depthLevel = 0;
	}
}
