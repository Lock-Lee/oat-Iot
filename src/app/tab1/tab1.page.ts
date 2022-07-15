import { Component, OnInit } from '@angular/core';
import { AppserviceService } from '../app.service';

@Component({
  selector: 'app-tab1',
  templateUrl: 'tab1.page.html',
  styleUrls: ['tab1.page.scss'],
})
export class Tab1Page implements OnInit {
  public gaugeType = 'semi';
  gaugeValue: any = 28.3;
  gaugeLabel = '';
  gaugeAppendText = '';

  constructor(public app:AppserviceService) { }
  ngOnInit(): void {
    this.settest();
  }

  settest() {

    setInterval(
      (e) => {
        var precision = 100; // 2 decimals
        var randomnum = Math.floor(Math.random() * (10 * precision - 1 * precision) + 1 * precision) / (1 * precision);
        this.gaugeValue = randomnum;

      },

      1000
    );
  }
}