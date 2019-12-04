using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class fountainmanager : MonoBehaviour
{

    private float nextTrigger = 0;
    private float scaleChangeInterval = 0.4f;
    private ParticleSystem ps;
    public OSC osc;
    private float foltyMod = 0;
    private float speedMod = 0;
    private float angleMod = 0;
    private int rateMod = 0;
    // Start is called before the first frame update
    void Start()
    {
        ps = gameObject.GetComponent<ParticleSystem>();
        osc.SetAddressHandler("/fountainX", MaxCallBackX);
        osc.SetAddressHandler("/fountainZ", MaxCallBackZ);
        osc.SetAddressHandler("/fountainY", MaxCallBackY);
        osc.SetAddressHandler("/fountainS", MaxCallBackS);
        osc.SetAddressHandler("/fountainR", MaxCallBackR);
        osc.SetAddressHandler("/fountainA", MaxCallBackA);
    }

    // Update is called once per frame
    void Update()
    {
        // assign new max height at an interval
        if (Time.time > nextTrigger)
        {
            var fOLT = ps.forceOverLifetime;
            var particlemain = ps.main;
            var shape = ps.shape;
            var rate = ps.emission;

            float randomheight = 8+Random.value * 4; 
            fOLT.y =-Mathf.RoundToInt(randomheight-foltyMod);
            particlemain.startSpeed = 17 + speedMod;
            shape.angle = 1.5f + angleMod;
            rate.rateOverTime = rateMod;
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

    void MaxCallBackY(OscMessage message)
    {
        float mes = message.GetFloat(0);
        foltyMod = mes;
    }
    void MaxCallBackS(OscMessage message)
    {
        float mes = message.GetFloat(0);
        speedMod = mes;
    }

    void MaxCallBackA(OscMessage message)
    {
        float mes = message.GetFloat(0);
        angleMod = mes;
    }

    void MaxCallBackR(OscMessage message)
    {
        float mes = message.GetFloat(0);
        rateMod = Mathf.RoundToInt(mes);
    }
}
