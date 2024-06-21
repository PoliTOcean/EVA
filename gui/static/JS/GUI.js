let info;
let script = document.currentScript;
let fullUrl = script.src;
let jsonUrl = fullUrl.replace("JS/GUI.js", "info.json");
let pages = ["ROV", "FLOAT", "PID", "TASK_1"];
let stsObj;

// [UTILS]
async function getRequest(url = '') {
    const response = await fetch(url, {
        method: 'GET',
        cache: 'no-cache',
        headers: {
            'Accept': 'application/json',
        },
    })
    return response.json();
}

async function postRequest(url, data) {
    const response = await fetch(url, {
        method: 'POST',
        cache: 'no-cache',
        headers: {
            'Accept': 'application/json',
        },
        body: JSON.stringify(data)
    })
    return response.json();
}



// Need this to prevent closing of server
function keep_alive_server() {
    let route = "/flaskwebgui-keep-server-alive";
    getRequest(route);
}


// [DYNAMIC PAGES HANDLER]
async function change(page) {
    if (page == page_now) return;
    if (page_now !== "home") document.getElementsByClassName(page_now)[0].classList.toggle("hide");
    document.getElementsByClassName(page)[0].classList.toggle("hide");
    page_now = page;
}

async function loadPages(page) {
    page_now = pages[page];
    const newpage = await (await fetch(page)).text();
    let parser = new DOMParser();
    let html = parser.parseFromString(newpage, "text/html");
    let wh = document.querySelectorAll(".window")[0];
    wh.append(html.body.firstChild);
}

const container = document.querySelector('.window');

const observer = new MutationObserver((mutationsList) => {
    for (const mutation of mutationsList) {
        if (mutation.type === 'childList') {
            const pid = container.querySelector("#PID_form");
            const task = container.querySelector("#TASK_1_FORM");
            // Se l'ultima pagina è pronta, carica i contenuti in tutte le pagine
            if (task && pid) {
                ROVLoader();
                Task1Loader();
                PIDLoader();
                observer.disconnect();
            }
        }
    }
});

observer.observe(container, { childList: true });



// [STATUSES MANAGMENT]

// * Trasforma il vettore in oggetto 

async function statusController() {
    let response = await fetch("/CONTROLLER/start_status");
    let status = await response.json();
    console.log(status);
    updateStatusesROV({"JOYSTICK": status["status"]});
}






// [MAIN]

window.onload = async () => {
    // Force dimensions of window
    let h = window.innerHeight;
    let w = window.innerWidth;
    let body = document.getElementsByTagName('body')[0];
    body.style.width = `${w}px`; 
    body.style.height = `${h}px`;

    // Load Info and divide
    info = await getRequest(jsonUrl);
    console.log(info)
    stsObj = info["statuses"].reduce((obj, key) => {
        obj[key] = false;
        return obj;
    }, {});


    // Load pages    
    for (let i = 0; i < pages.length; i++) loadPages(pages[i]);
    page_now = "home";
       
    // Routines
    let refresh = 2000;
    setInterval(() => statusFLOAT("STATUS"), refresh);
    setInterval(statusController, refresh);
    setInterval(keep_alive_server, refresh + 1000);
}





// const socket = io("ws://127.0.0.1:5000",{
    // transports: ["websocket"],
    // reconnectionDelayMax: 10000,
// }) 


// socket.on("connect",() => {
    // console.info("[Socket.io] Ready");
    // socket.emit("test", "test");
// });

// socket.on("connect_error", (data) => {
    // console.error("ERROR");
    // console.log(data);
// });
    
// socket.on("disconnect", (reason, details) => {
    // console.info("DISCONNECTED");
    // console.log(reason);
    // console.log(details);
// });

// socket.on('error', (error) => {
    // console.error('ERROR');
    // console.log(error);
// });


