@extends('layouts.main')
@section('title')
    Authentication
@endsection
@section('content')
 <!-- App Capsule -->
 <div id="appCapsule">
    <h1 class="" style="font-size: 40px;font-family: courier,arial,helvetica;color: #2b98ef;text-align: center;">Finito Cloud</h1>
    <div class="section mt-2 text-center">
        <h1>Log in</h1>
        <h4>Fill the form to log in</h4>
    </div>
    <div class="section mb-5 p-2">

        <form method="POST" action="{{ route('login') }}">
            @csrf
            <div class="card">
                <div class="card-body pb-1">
                    <div class="form-group basic">
                        <div class="input-wrapper">
                            <label class="label" for="email1">E-mail</label>
                            <input id="email" type="email" class="form-control @error('email') is-invalid @enderror" name="email" value="{{ old('email') }}" required autocomplete="email" autofocus>
                            @error('email')
                                <span class="invalid-feedback" role="alert">
                                    <strong>{{ $message }}</strong>
                                </span>
                            @enderror
                            <i class="clear-input"><ion-icon name="close-circle"></ion-icon></i>
                        </div>
                    </div>

                    <div class="form-group basic">
                        <div class="input-wrapper">
                            <label class="label" for="password1">Password</label>
                            <input id="password" type="password" class="form-control @error('password') is-invalid @enderror" name="password" required autocomplete="current-password">
                            @error('password')
                                <span class="invalid-feedback" role="alert">
                                    <strong>{{ $message }}</strong>
                                </span>
                            @enderror
                            <i class="clear-input"><ion-icon name="close-circle"></ion-icon></i>
                        </div>
                    </div>
                    <div class="form-group row">
                        <div class="col-md-6 offset-md-4">
                            <div class="form-check">
                                <input class="form-check-input" type="checkbox" name="remember" id="remember" {{ old('remember') ? 'checked' : '' }}>

                                <label class="form-check-label" for="remember">
                                    {{ __('Remember Me') }}
                                </label>
                            </div>
                        </div>
                    </div>
                </div>
            </div>


            <div class="form-links mt-2">
                <div>
                <a href="{{ route('register') }}">Register Now</a>
                </div>
                <div><a href="{{ route('login') }}" class="text-muted">Forgot Password?</a></div>
            </div>

            <div class="form-button-group  transparent">
                <button type="submit" class="btn btn-primary btn-block btn-lg">Log in</button>
            </div>

        </form>
    </div>

</div>
<!-- * App Capsule -->


@endsection
