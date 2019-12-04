using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class maxflow : MonoBehaviour
{
    private float nextTime = 0;
    private float rateof = 0.01f;
    public OSC osc;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        if (Time.time > nextTime)
        {
            float posx = gameObject.transform.position.x;
            float posy = gameObject.transform.position.y;
            OscMessage message = new OscMessage();
            message.address = "/rotation";
            message.values.Add(gameObject.transform.rotation.y);
            osc.Send(message);

            nextTime = Time.time + rateof;

        }
    }
}
