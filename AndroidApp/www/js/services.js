'use strict';

/* Services */


// Demonstrate how to register services
// In this case it is a simple value service.
angular.module('pic32kit.services', [])
    .factory("Cities", function() {
        function Cities() {
            this.list = [
                {name: 'Hong Kong'},
                {name: 'Shanghai'},
                {name: 'Beijing'}
            ];
            this.selected = this.list[0];
        }

        Cities.prototype = {
            getList: function() {
                return(this.list);
            },
            getSelected: function() {
                return(this.selected);
            },
            selectNext: function() {
                var i = this.findIndexByName(this.selected.name) + 1;
                if (i >= this.list.length)
                    i = 0;
                this.selected = this.list[i];
            },
            selectPrev: function() {
                var i = this.findIndexByName(this.selected.name) - 1;
                if (i < 0)
                    i = this.list.length - 1;
                this.selected = this.list[i];
            },
            findIndexByName: function(name) {
                var length = this.list.length;
                for (var i = 0; i < length; i++) {
                    if (this.list[i].name === name)
                        return i;
                }
                return -1;
            }
        };

        Cities.create = function() {
            return(new Cities());
        };

        return(Cities);
    })
    
    .factory("Leds", function() {
        function Leds() {
            this.list = [
                {
                    id: 3, // led3
                    name: 'LED3',
                    status: 'off'
                }, {
                    id: 2, // led2
                    name: 'LED2',
                    status: 'off'
                }, {
                    id: 1, // led1
                    name: 'LED1',
                    status: 'off'
                }
            ];
        }

        Leds.prototype = {
            getList: function() {
                return(this.list);
            },
            getStatus: function(id) {
                var i = this.findIndexById(id);
                if (i >= 0) {
                    return this.list[i].status;
                }
                return null;
            },
            updateStatus: function(id, status) {
                var i = this.findIndexById(id);
                if (i >= 0) {
                    if (status === 'on' || status === 'off') {
                        this.list[i].status = status;
                        return true;
                    }
                }
                return false;
            },
            findIndexById: function(id) {
                var length = this.list.length;
                for (var i = 0; i < length; i++) {
                    if (this.list[i].id === id)
                        return i;
                }
                return -1;
            }
        };

        Leds.create = function() {
            return(new Leds());
        };

        return(Leds);
    })
    
    .factory("Buttons", function() {
        function Buttons() {
            this.list = [
                {
                    id: 3, // sw3
                    name: 'Next',
                    status: 'up',
                    onmousedown: function() {
                        console.log('onmousedown: SW3');
                    },
                    onmouseup: function() {
                        console.log('onmouseup: SW3');
                    },
                    onclick: function() {
                        console.log('onclick: SW3');
                    }
                }, {
                    id: 2, // sw2
                    name: 'Prev',
                    status: 'up',
                    onmousedown: function() {
                        console.log('onmousedown: SW2');
                    },
                    onmouseup: function() {
                        console.log('onmouseup: SW2');
                    },
                    onclick: function() {
                        console.log('onclick: SW2');
                    }
                }, {
                    id: 1, // sw1
                    name: 'LED1',
                    status: 'up',
                    onmousedown: function() {
                        console.log('onmousedown: SW1');
                    },
                    onmouseup: function() {
                        console.log('onmouseup: SW1');
                    },
                    onclick: function() {
                        console.log('onclick: SW1');
                    }
                }
            ];
        }

        Buttons.prototype = {
            getList: function() {
                return(this.list);
            },
            setMousedownFn: function(id, fn) {
                var i = this.findIndexById(id);
                if (i >= 0) {
                    this.list[i].onmousedown = fn;
                    return true;
                }
                return false;
            },
            setMouseupFn: function(id, fn) {
                var i = this.findIndexById(id);
                if (i >= 0) {
                    this.list[i].onmouseup = fn;
                    return true;
                }
                return false;
            },
            isStatusChanged: function(id, status) {
                var i = this.findIndexById(id);
                if (i >= 0) {
                    return(this.list[i].status !== status);
                }
                return false;
            },
            updateStatus: function(id, status) {
                var i = this.findIndexById(id);
                if (i >= 0) {
                    if (status === 'up' || status === 'down') {
                        this.list[i].status = status;
                        return true;
                    }
                }
                return false;
            },
            findIndexById: function(id) {
                var length = this.list.length;
                for (var i = 0; i < length; i++) {
                    if (this.list[i].id === id)
                        return i;
                }
                return -1;
            }

        };

        Buttons.create = function() {
            return(new Buttons());
        };

        return(Buttons);
    })
    
    .factory("Weather", function($http) {
        // Define the constructor function.
        function Weather() {
            this.city = null;   // city name
            this.desc = null;   // weather description
            this.brief = null;  // description in brief
            this.icon = null;   // weather icon
            this.temp = null;   // temperature
            this.time = null;   // time of weather info
        }

        // Define the "instance" methods using the prototype
        // and standard prototypal inheritance.
        Weather.prototype = {
            getCity: function() {
                return(this.city);
            },
            setCity: function(city) {
                this.city = city;
            },
            getDesc: function() {
                return(this.desc);
            },
            setDesc: function(desc) {
                this.desc = desc;
            },
            getBrief: function() {
                return(this.brief);
            },
            setBrief: function(brief) {
                this.brief = brief;
            },
            getIcon: function() {
                return(this.icon);
            },
            setIcon: function(icon) {
                this.icon = icon;
            },
            getTemperature: function() {
                return(this.temp);
            },
            setTemperature: function(temp) {
                this.temp = temp;
            },
            getTime: function() {
                return(this.time);
            },
            setTime: function(time) {
                this.time = time;
            },
            getIconUrl: function() {
                if (this.icon) {
                    var url = 'http://openweathermap.org/img/w/' + this.icon + '.png';
                    return url;
                }
                return('img/cancel_24.png');
            },
            updateWeather: function(city) {
                var url = "http://api.openweathermap.org/data/2.5/weather?q=json&callback=JSON_CALLBACK&q=";
                var thisObj = this;
                //$log.debug("url = " + url);
                //console.log("city = " + city);
                $http({
                    method: 'JSONP', url: url + city
                }).success(function(data) {
                    //console.log(JSON.stringify(data, null, 4));
                    //$log.debug(JSON.stringify(data, null, 4));
                    thisObj.setDesc(data.weather[0].description);
                    thisObj.setBrief(data.weather[0].main);
                    thisObj.setIcon(data.weather[0].icon);
                    thisObj.setTemperature(data.main.temp);
                    thisObj.setTime(data.dt * 1000);
                }).error(function(data, status, headers, config) {
                    console.error(JSON.stringify(data));
                    console.error(JSON.stringify(status));
                    console.error(JSON.stringify(headers));
                    console.error(JSON.stringify(config));
                    thisObj.setIcon(null);
                    thisObj.setBrief(null);
                    thisObj.setDesc(null);
                    thisObj.setTemperature(null);
                    thisObj.setTime(null);
                });
            }
        };

        // Define the "class" / "static" methods. These are
        // utility methods on the class itself; they do not
        // have access to the "this" reference.
        Weather.create = function() {
            return(new Weather());
        };

        // Return constructor - this is what defines the actual
        // injectable in the DI framework.
        return(Weather);
    })
    
    .factory('cordovaReady', function() {
        return function(fn) {
            var queue = [];
            var impl = function() {
                queue.push(Array.prototype.slice.call(arguments));
            };
            document.addEventListener('deviceready', function() {
                queue.forEach(function(args) {
                    fn.apply(this, args);
                });
                impl = fn;
            }, false);
            return function() {
                return impl.apply(this, arguments);
            };
        };
    })
    
    .factory('Starterkit',
        function(cordovaReady) {
            return {
                start: cordovaReady(function() {
                    cordova.exec(
                        function(arg) {
                            console.log('Starterkit.start() success: ' + arg);
                        },
                        function(err) {
                            console.log('Starterkit.start() error: ' + err);
                        },
                        "StarterkitPlugin", "start", []
                        );
                }),
                stop: function() {
                    cordova.exec(
                        function(arg) {
                            console.log('Starterkit.stop() success: ' + arg);
                        },
                        function(err) {
                            console.log('Starterkit.stop() error: ' + err);
                        },
                        "StarterkitPlugin", "stop", []
                        );
                },
                userActionLed: function(id, status) {
                    // send user action on led to accessory
                    //console.log('Starterkit.userActionLed(): id = ' + id + ', status = ' + status);
                    cordova.exec(
                        function(arg) {
                            console.log('Starterkit.userActionLed() success: ' + arg);
                        },
                        function(err) {
                            console.log('Starterkit.userActionLed() error: ' + err);
                        },
                        "StarterkitPlugin", "userActionLed", [id, status]
                        );
                },
                userActionButton: function(id, status) {
                    // send user action on sw to accessory
                    //console.log('Starterkit.userActionButton(): id = ' + id + ', status = ' + status);
                    cordova.exec(
                        function(arg) {
                            console.log('Starterkit.userActionButton() success: ' + arg);
                        },
                        function(err) {
                            console.log('Starterkit.userActionButton() error: ' + err);
                        },
                        "StarterkitPlugin", "userActionButton", [id, status]
                        );
                },
                echo: function(str) {
                    cordova.exec(
                        function(arg) {
                            console.log('Starterkit.echo() success: ' + arg);
                        },
                        function(err) {
                            console.log('Starterkit.echo() error: ' + err);
                        },
                        "StarterkitPlugin", "echo", [str]
                        );
                }
            };
        })

    .factory("ToggleLed", function(Starterkit) {
        function ToggleLed() {
            this.interval_id = -1;
        }

        ToggleLed.prototype = {
            start: function(id, ms) {
                var led_id = id;
                var interval_ms = ms;
                var led_state = 'off';
                this.interval_id = setInterval(function() {
                    console.log('ToggleLed id=' + led_id);
                    Starterkit.userActionLed(led_id, led_state);
                    led_state = led_state === 'on' ? 'off' : 'on';
                }, interval_ms);
            },
            stop: function() {
                clearInterval(this.interval_id);
            }
        };

        ToggleLed.create = function(id, ms) {
            return(new ToggleLed(id, ms));
        };

        return(ToggleLed);
    })

    .value('version', '0.1');
