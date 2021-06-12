$fn = 200;

linear_extrude(height = 6.35) {
    difference() {
        circle(d = 5 + 2 * 4);
        circle(d = 5);
    }
}