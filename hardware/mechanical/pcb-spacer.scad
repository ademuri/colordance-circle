$fn = 200;

function inches(in) = in * 25.4;

module spacer(height, id, od) {
    linear_extrude(height = height) {
        difference() {
            circle(d = od);
            circle(d = id);
        }
    }
}

// #8 PCB spacer
//spacer(height = 6.35, od = 5 + 2 * 4, id = 5);

// 1/4-20 bolt washer
spacer(height = 1, id = inches(.257), od = inches(.257) + 2 * 4);