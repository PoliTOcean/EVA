let prof = "1";
let copy= undefined;
let sub_but;


function areObjectsEqual(obj1, obj2) {
    const keys1 = Object.keys(obj1);
    const keys2 = Object.keys(obj2);

    if (keys1.length !== keys2.length) {
        return false;
    }

    for (let key of keys1) {
        const val1 = obj1[key];
        const val2 = obj2[key];

        if (typeof val1 === "object" && typeof val2 === "object") {
            if (!areObjectsEqual(val1, val2)) {
                return false;
            }
        } else {
            if (val1 !== val2) {
                return false;
            }
        }
    }

    return true;

}


function loadProfile(num) { 
    prof = `${num}`;
    // I'm not crazy, is a way to do deep copy of an object
    if (copy == undefined) copy = JSON.parse(JSON.stringify(info["PID"]));
    document.querySelector(".checkbox").checked = copy[prof]["enabled"]
    Object.keys(copy[`${num}`]["settings"]).forEach(el => document.querySelector(`#${el}`).value = parseFloat(copy[`${num}`]["settings"][el]))
}


async function submit() {
    if (areObjectsEqual(info["PID"], copy)) {
        console.log("Oggetti uguali")
        return; 
    }
    let active = Object.keys(copy).find(el => copy[el]["enabled"])

    if (!active) {
        alert("DEACTIVATED PID")   
        mqtt_c.publish('PID/', JSON.stringify(copy["0"]));
    } else {
        mqtt_c.publish('PID/', JSON.stringify(copy[active]));
    }
    info["PID"] = JSON.parse(JSON.stringify(copy));
    let f = await postRequest("/PID/set", copy);
    loadProfile(+prof);
}


function PIDLoader() {
    sub_but = document.querySelector("#sbm_bu");


    // ! DROPDOWN
    document.querySelectorAll('.dropdown').forEach(function(dropdown) {
        dropdown.addEventListener('click', function() {
            this.setAttribute('tabindex', 1);
            this.classList.toggle('active');
            var dropdownMenu = this.querySelector('.dropdown-menu');
            if (dropdownMenu.style.display === 'block') {
                dropdownMenu.style.display = 'none';
            } else {
                dropdownMenu.style.display = 'block';
            }
        });

        dropdown.addEventListener('focusout', function() {
            this.classList.remove('active');
            this.querySelector('.dropdown-menu').style.display = 'none';
        });

        dropdown.querySelectorAll('.dropdown-menu li').forEach(function(item) {
            item.addEventListener('click', function() {
                var dropdownParent = this.closest('.dropdown');
                dropdownParent.querySelector('span').textContent = this.textContent;
                dropdownParent.querySelector('input').setAttribute('value', this.getAttribute('id'));
                loadProfile(this.textContent.match(/\d+/)[0])
            });
        });
    });

    document.querySelector('.dropdown').querySelector("span").textContent = "Profile 1"
    loadProfile(1)


    // ! Change values
    function checkSubmit() {
        let f = 0;
        Object.keys(info["PID"]).forEach(el => {
            if (!areObjectsEqual(info["PID"][el], copy[el])) f = 1;
        })
        if (f) sub_but.classList.remove("disabled");
        else sub_but.classList.add("disabled");

    }


    document.querySelector(".checkbox").addEventListener("change", (event) => {
        copy[prof]["enabled"] = event.target.checked;
        Object.keys(copy).forEach(key => {
            if (copy[key]["enabled"] && key != prof) {
                copy[key]["enabled"] = false;
                alert(`Attention, deactivated profile ${key}`)
            }
        })
        checkSubmit();
    })
    
    document.querySelectorAll(".input").forEach((el) => {
        el.addEventListener('input', (event) => {
            copy[prof]["settings"] = {
                ...copy[prof]["settings"],
                [event.target.id]: parseFloat(event.target.value),
            }
            checkSubmit();
        });
    });
}