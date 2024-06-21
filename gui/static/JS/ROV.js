let page_now;

addEventListener("resize", (event) => {
    let h = window.innerHeight;
    let w = window.innerWidth;
    let body = document.getElementsByTagName('body')[0];
    body.style.width = `${w}px`; 
    body.style.height = `${h}px`;
});


// [CAMERA MANAGMENT]

function switching(id) {
    let n_camera = `${id.match(/\d+/)[0]}`;
    if (info["cameras"][n_camera]["status"] == 0) return;
    let z = -1;
    for (let i = 0; i < info["cameras"]["n_cameras"] && z == -1; i++) if (info["cameras"][`${i}`]["status"] == 0) z = i;
    let camera_p = document.querySelector(".camera_p");
    let camera_s = document.querySelectorAll(`.camera_s`);
    let target, deploy;
    camera_s.forEach((el) => {
        if (el.firstElementChild.id == `c${n_camera}`) {
            target = el.firstElementChild;
            deploy = el;
        }
    });
    camera_p.append(target);
    deploy.append(camera_p.firstElementChild);
    info["cameras"][n_camera]["status"] = 0;
    info["cameras"][z]["status"] = 1;
}

async function onoff(id) {
    let wh = document.querySelectorAll(`#c${id.match(/\d+/)[0]}`)[0];
    console.log(wh);
    console.log(info)
    info["cameras"][`${id.match(/\d+/)[0]}`]["enabled"] = !info["cameras"][`${id.match(/\d+/)[0]}`]["enabled"];
    if (info["cameras"][`${id.match(/\d+/)[0]}`]["enabled"] == 1) wh.className = wh.className.replace(" hide", "");
    else wh.className += " hide";
}

// [LOADER INSTRUMENTS]
let attitude;
let compass;


const options_instruments = {
    size: 200, 
    roll: 0,  
    pitch: 0, 
    turn: 0,  
    heading: 0, 
    verticalSpeed: 0, 
    airspeed: 0,
    altitude: 0, 
    pressure: 1000,
    hideBox: true,
    // LIBRERIE MERDOSE, NON SAPETE GESTIRE NEANCHE UN PATH 
    imagesDirectory: "/static/SVG",
};


function PIDhandler(pidElement, val) {
    switch (val) {
        case 0:
            pidElement.classList.remove("on");
            pidElement.classList.remove("stoppable");
            break;
        case 1:
            pidElement.classList.add("stoppable");
            pidElement.classList.remove("on");
            break;
        case 2:
            pidElement.classList.add("on");
            pidElement.classList.remove("stoppable");
            break;
    }
}

function updateStatusesROV(obj) {
    const statuses = document.getElementsByClassName("status STATUSES");
    Object.keys(obj).forEach((key) => stsObj[key] = obj[key]);
    Array.from(statuses).forEach((sts, index) => {
        let txt = sts.querySelector("label span").textContent.trim();
        if (txt in obj) stsObj[txt] = obj[txt];
        if (txt == "PID") return PIDhandler(statuses[index], stsObj[txt]); 
        // Update in DOM
        if (stsObj[txt]) statuses[index].classList.add("on");
        else statuses[index].classList.remove("on");
    });
}


function updateIMU(imuJSON) {
    attitude.updatePitch(imuJSON["PITCH"]);
    attitude.updateRoll(imuJSON["ROLL"]);
    compass.updateHeading(imuJSON["YAW"]);
}



function updateSensors(sensorsJSON) {
    const depth = document.querySelector("#data_depth");
    const temp = document.querySelector("#data_tempExt");
    temp.innerHTML = `${parseFloat(sensorsJSON["tempExt"]).toFixed(2)} °C`;
    depth.innerHTML = `${parseFloat(sensorsJSON["depth"]).toFixed(2)} m`;

}

function ROVLoader() {
    const attitudeElement = document.querySelector("#attitude");
    const compassElement = document.querySelector("#compass");
    attitude = new FlightIndicators(
        attitudeElement,
        FlightIndicators.TYPE_ATTITUDE,
        options_instruments
    );
    compass = new FlightIndicators(
        compassElement,
        FlightIndicators.TYPE_HEADING,
        options_instruments
    );
}
