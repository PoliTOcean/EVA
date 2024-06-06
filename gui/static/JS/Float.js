let nReport = 1;
let mux = 1;
let listening = 0;

async function startFloat() {
    return await getRequest("/FLOAT/start");
}


function publishReport(data) {
    const tab = document.getElementsByClassName("g1")[0];
    let img_el = [document.createElement('img'), document.createElement('img')];
    img_el.forEach((i) => i.classList.add("img_style"))
    let div = document.createElement('div');
    let h1 = document.createElement('h1');
    let h2 = [document.createElement('h2'), document.createElement('h2')];
    let p = document.createElement('p');
    h1.innerText = `REPORT #${nReport++}`;
    div.classList.add('report');
    p.classList.add('raw');
    console.log(data.data)
    let {raw, img} = data.data;
    if (img != "NO_DATA") {
        p.innerHTML = "";
        for (let i = 0; i < raw.times.length; i++) {
            p.innerHTML += `${raw.company_name}&emsp;${raw.times[i]}&emsp;${raw.pressure[i]} Pa&emsp;${raw.depth[i]} m<br/>`;
        }
        img_el[0].src = "data:image/jpeg;charset=utf-8;base64," + img[0];
        img_el[1].src = "data:image/jpeg;charset=utf-8;base64," + img[1];
        div.append(h1);
        h2[0].innerHTML = `Data received:`
        div.append(h2[0]);
        div.append(p);
        h2[1].innerHTML = "Plots:"
        div.append(h2[1]);
        div.append(img_el[0]);
        div.append(img_el[1]);
        tab.appendChild(div);
    }
    else {
        div.append(h1);
        p.innerText = `NO DATA`;
        tab.appendChild(div);
    }
}

function publishPackage(status) {
    raw = status['text'];
    console.log(raw);
    const tab = document.getElementsByClassName("g1")[0];
    let div = document.createElement('div');
    let h1 = document.createElement('h1');
    let p = document.createElement('p');
    h1.innerHTML = "PACKAGE";
    p.innerHTML += `${raw.company_name}&emsp;${raw.times}&emsp;${raw.pressure} Pa&emsp;${raw.depth} m<br/>`;
    div.classList.add('report');
    p.classList.add('raw');
    div.append(h1);
    div.append(p);
    tab.appendChild(div);
}


async function listeningFLOAT() {
    const immersion = document.getElementsByClassName("status IMMERSION")[0];
    const listen = document.getElementsByClassName("status LISTENING")[0];
    sts = await getRequest("/FLOAT/listen");
    if (sts["text"] != "LOADING") {
        publishReport(sts);
        listening = 0;
        immersion.classList.remove("immersion");
        listen.classList.remove("listening");
    }
    console.log(sts);
}

async function handleStatus(status) {
    const serial = document.getElementsByClassName("status SERIAL")[0];
    const ready = document.getElementsByClassName("status READY")[0];
    const drop = document.getElementsByClassName("status DROP");
    const immersion = document.getElementsByClassName("status IMMERSION")[0];
    const listen = document.getElementsByClassName("status LISTENING")[0];
    const auto_mode = document.querySelector(".status.AUTO_MODE");
    const conn = document.querySelector(".status.CONN");
    if (!status.status) status = await startFloat();
    console.log(status);
    sts = status.text.split("|");
    for (let i = 0; i < sts.length; i++) {
        switch (sts[i].trim()) {
            case "CONNECTED":
                serial.classList.add("on");
                ready.classList.remove("on");                
                for (let i = 0; i < drop.length; i++) {
                    drop[i].classList.remove("clickable");
                    drop[i].classList.add("disabled");
                }
                mux = 0;
                break;

            case "CONNECTED&READY":
                serial.classList.add("on");
                ready.classList.add("on");                
                for (let i = 0; i < drop.length; i++) {
                    drop[i].classList.add("clickable");
                    drop[i].classList.remove("disabled");
                }
                mux = 1;
                break;
            case "IMMERSION":
                for (let i = 0; i < drop.length; i++) drop[i].classList.remove("clickable");
                mux = 0;
                immersion.classList.add("immersion");
                break;
            case "UPLOAD_DATA":
                for (let i = 0; i < drop.length; i++) drop[i].classList.remove("clickable");
                mux = 0;
                listen.classList.add("listening");
                listening = 1;
                listeningFLOAT();
            case "DATA_ABORTED":
                mux = 0;
                break
            case "NO USB":
                serial.classList.remove("on");
                ready.classList.remove("on");
                for (let i = 0; i < drop.length; i++) drop[i].classList.remove("enabled");
                mux = 0;
            case "AUTO_MODE_NO":
                auto_mode.classList.remove("on");
                break;
            case "AUTO_MODE_NO":
                auto_mode.classList.add("on");
                break;
            case "CONN_OK":
                conn.classList.add("on");
                break;
            case "CONN_LOST":
                conn.classList.remove("on");
                break;
        }
    }
}


async function statusFLOAT(msg) {
    if (listening) {
        listeningFLOAT()    
        return;
    }
    let data = await getRequest(`/FLOAT/status?msg=${msg}`);
    switch (msg) {
        case "STATUS":
            handleStatus(data);
            break
        case "SEND_PACKAGE":
            publishPackage(data);
            break
    }
}

let msgs = ["GO", "SWITCH_AUTO_MODE", "TRY_UPLOAD", "BALANCE", "CLEAR_SD"]

async function msg(e, msg_id) {
    if (!mux) {
        console.log("NOT READY FOR MSG");
        return;
    }
    mux = 0;
    const data = await fetch(`FLOAT/msg?msg=${msgs[msg_id]}`);
    if (data.status == 201) mux = 1;
    else alert("Is USB cable connected?")
}
