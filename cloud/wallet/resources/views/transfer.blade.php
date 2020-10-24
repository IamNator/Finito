@extends('layouts.main')
@section('title')
    Transfer Funds
@endsection
@section('content')

    <!--Dashboard top-->
    <section class="section-padding-sm-2 blue-bg">
        <div class="container">
            <div class="row">
                <div class="col-xl-4 col-lg-4 col-md-6 col-sm-6 mb-20">
                    <div class="card">
                        <div class="card-header">
                             Profile <a href="#"><i class="ti-arrow-top-right"></i></a>
                        </div>
                        <div class="card-body">
                        <p>Good Morning! <strong>{{ Auth::user()->name }}</strong></p>
                        <p>You joined In: <strong>{{ Auth::user()->created_at }}</strong></p>
                        </div>
                    </div>
                </div>
                <div class="col-xl-4 col-lg-4 col-md-6 col-sm-6 mb-20">
                    <div class="card">
                        <div class="card-header">
                            Balance
                        </div>
                        <div class="card-body">
                            <p>US Doller: <strong>${{ Auth::user()->wallet*380 }}</strong></p>
                            <p>NG Niara: <strong>NGN{{ Auth::user()->wallet }}</strong></p>
                        </div>
                    </div>
                </div>
                <div class="col-xl-4 col-lg-4 col-md-6 col-sm-6 mb-20">
                    <div class="card">
                        <div class="card-header">
                            Bank Details
                        </div>
                        <div class="card-body">
                        <p>Name: <strong>{{ Auth::user()->name }}</strong></p>
                            <p>Number: <strong>{{ Auth::user()->number }}</strong></p>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </section><!--Dashboard top-->


    <!--Dashboard Bottom-->
    <section class="section-padding-sm-2 blue-bg-2">
        <div class="container">
            @if (session('success'))
    <div class="alert alert-success  alert-dismissible fade show" id="alert" role="alert">
        <button type="button" id="close" class="close" data-dismiss="alert">x</button>
        <li>
            {{ session('success') }}
        </li>
    </div>
@endif

@if (session('failure'))
    <div class="alert alert-danger alert-dismissible fade show" id="alert" role="alert">
        <button type="button" id="close" class="close" data-dismiss="alert">x</button>
       <li>
           {{ session('failure') }}
       </li>
    </div>
@endif

            <div class="row justify-content-center">
                <div class="col-xl-3 col-lg-3 col-md-6 col-sm-6 mb-20">
                    <div class="card mb-30">
                        <div class="card-header">
                            Someone to pay?
                        </div>
                        <div class="card-body">
                            <p>Send money straight to another user or bank</p>
                            <a data-toggle="modal" data-target="#ModalCenter1" class="bttn-small btn-fill"><i class="ti-user"></i> Make a payment</a>
                        </div>
                    </div>
                    <div class="card">
                        <div class="card-header">
                            Receive a payment?
                        </div>
                        <div class="card-body">
                            <p>Fund your account instantly straight from any bank/card.</p>
                            <a data-toggle="modal" data-target="#ModalCenter2" class="bttn-small btn-fill"><i class="ti-direction"></i> Receive payment</a>
                        </div>
                    </div>
                </div>
                <div class="col-xl-9 col-lg-9 col-md-12 mb-20">
                    <div class="card">
                        <div class="card-header">
                            Transfer Funds
                        </div>
                        <div class="card-body">
                            <div class="sent-success">
                                <h3>You are sending {{ $amount }}</h3>
                            <p><strong>to {{ $trans->name }}, click the send button to complete</strong></p>
                            <form method="post" action="{{ route('send.submit') }}">
                                @csrf
                                <textarea name="description" placeholder="Enter description" class="form-control"></textarea>
                                <br>
                            <input type="hidden" name="amount" value="{{ $amount }}">
                            <input type="hidden" name="number" value="{{ $trans->number }}">
                            <input type="hidden" name="id" value="{{ $trans->id }}">
                            <input type="hidden" name="wallet" value="{{ $trans->wallet }}">
                            <button type="submit" class="bttn-small btn-fill">Send</button>
                            </form>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </section><!--Dashboard Bottom-->


@endsection
