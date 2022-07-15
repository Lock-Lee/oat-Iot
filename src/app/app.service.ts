import { Injectable, OnInit } from '@angular/core';
const Microgear: any = window;

var microgear = Microgear.Microgear.create({
  key: 'YykoWTP3PCI2xrB',
  secret: '1vwDh4mTk0WxS1xI0p4eyREmM',
  alias: 'Ionic' /*  optional  */,
});
@Injectable({
  providedIn: 'root',
})
export class AppserviceService implements OnInit {
public status_con
  constructor() {
    microgear.connect('Jokeiot');

    microgear.on('connected', () => {
      microgear.subscribe('/Jokeiot/+');
    });
    this.present()
   
  }
  ngOnInit(){
    this.present()
  }
public  present  =  () => {
    microgear.on('present', (event) => {
     
      this.status_con = String(event.type)
    
      
    });
    return  this.status_con
  };
  message = (value) => {
    microgear.on('message', (topic, msg) => {
      value({ topic: topic, message: msg });

      console.log(msg);
    });
  };

  publish = (topic, message) => {
    microgear.publish('/joke' + topic, message);
  };
}