using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class fountainmanager : MonoBehaviour
{

    private float nextTrigger = 0;
    private float scaleChangeInterval = 0.4f;
    private ParticleSystem ps;
    public OSC osc;

    // Start is called before the first frame update
    void Start()
    {
        ps = gameObject.GetComponent<ParticleSystem>();
        osc.SetAddressHandler("/fountainX", MaxCallBackX);
        osc.SetAddressHandler("/fountainZ", MaxCallBackZ);
    }

    // Update is called once per frame
    void Update()
    {
        // assign new max height at an interval
        if (Time.time > nextTrigger)
        {
            var fOLT = ps.forceOverLifetime;
            float randomheight = 8+Random.value * 4; 
            fOLT.y = -Mathf.RoundToInt(randomheight);
            nextTrigger = Time.time + scaleChangeInterval;
        //    Debug.Log(randomheight);
        }
    }

    void MaxCallBackX(OscMessage message)
    {
        float mes = message.GetFloat(0);
        var fOLT = ps.forceOverLifetime;
        fOLT.x = mes;
    }

    void MaxCallBackZ(OscMessage message)
    {
        float mes = message.GetFloat(0);
        var fOLT = ps.forceOverLifetime;
        fOLT.z = mes;
    }
}
