// * TASK 3.4

function Task1Loader() {
    document.getElementById('fileInput').addEventListener('change', function(event) {
        uploadFile(event);
    });
}

function publishPlot(data) {
    const tab = document.getElementsByClassName("task1_res")[0];
    if (tab.hasChildNodes()) tab.removeChild(tab.firstChild);
    let img = document.createElement('img');
    let div = document.createElement('div');
    div.classList.add('task1_report');
    if (data.data != "NO_DATA") {
        img.src = "data:image/jpeg;charset=utf-8;base64," + data.data;
        div.append(img);
        tab.appendChild(div);
    }
    else {
        let p = document.createElement('p');
        div.append(p);
        p.innerText = `NO DATA`;
        tab.appendChild(div);
    }
}

function uploadFile(event) {
    const file = event.target.files[0];
    if (file && file.type === 'text/csv') {
        const formData = new FormData();
        formData.append('file', file);
        fetch('/TASK_1/file', {
            method: 'POST',
            body: formData
        })
        .then(response => response.json())
        .then(data => {
            console.log('Success:', data);
            document.getElementById('fileInfo').innerHTML = `Success!`;
            console.log(data);
            publishPlot(data);
        })
        .catch(error => {
            console.error('Error:', error);
            document.getElementById('fileInfo').innerHTML = `Error`;
        });
    } else {
        alert('Not a CSV');
    }
    // delete buffer upload
    event.target.value = '';
    if (e.target.value) {
        e.target.type = 'text';
        e.target.type = 'file';
    }
}


// * TASK 3.3

let photo_interval;
let started = 0;
let processing = 0;
let counter = 0;

async function statusPhotogrammetry() {
    const data = await getRequest("/PHOTO/status");
    const label = document.querySelector(".photo_status");
    const button = document.querySelector(".cat.status.PHOTO");
    const button_text = document.querySelector(".start_stop");
    let sts = data["status"];
    console.log(data)
    switch (sts) {
        case "FINISHED":
            button.classList.remove("stoppable");
            button.classList.add("clickable");
            processing = 0;
            started = 0;
            button_text.innerHTML = "Start";
            clearInterval(photo_interval);
            break;
    }
    label.innerHTML = sts;
}

async function startPhotogrammetry(element) {
    if (processing) return;
    const button_text = element.querySelector(".start_stop");
    if (started) {
        data = await getRequest("/PHOTO/stop");
        button_text.innerHTML = "Waiting";
        element.classList.remove("stoppable");
        element.classList.remove("clickable");
        element.classList.add("disabled");
        processing = 1;
        return;    
    }
    data = await getRequest("/PHOTO/start");
    button_text.innerHTML = "Stop";
    element.classList.add("stoppable");
    photo_interval = setInterval(statusPhotogrammetry, 2000);
    started = 1;
    counter = 0;
    document.querySelector(".photo_counter").innerHTML = counter;
}

function handleTask(cmd) {
    if (cmd.search("SNAP") == 0 && started && !processing) {
        counter++;
        document.querySelector(".photo_counter").innerHTML = counter;
    }
}